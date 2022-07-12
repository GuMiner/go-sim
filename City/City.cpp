#include <iostream>
#include <memory>
#include "City.h"

City::City() : 
    cameraVelocity(Ogre::Vector3::ZERO),
    pressedKeys(),
    camera(nullptr),
    populace(nullptr),
    OgreBites::ApplicationContext("City")
{
    pressedKeys['w'] = false;
    pressedKeys['a'] = false;
    pressedKeys['s'] = false;
    pressedKeys['d'] = false;
    pressedKeys['r'] = false;
    pressedKeys['f'] = false;
}

void City::setup()
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // register for input events
    addInputListener(this);

    // get a pointer to the already created root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen    
    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);

    Ogre::Light* l = scnMgr->createLight("tstLight");
    l->setType(Ogre::Light::LT_DIRECTIONAL);
    l->setDiffuseColour(Ogre::ColourValue::White);
    l->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

    auto ln = scnMgr->getRootSceneNode()->createChildSceneNode();
    ln->setDirection(Ogre::Vector3(0.55, -0.3, 0.75).normalisedCopy());
    ln->attachObject(l);


    scnMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
    scnMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");

    // also need to tell where we are
    camera = scnMgr->getRootSceneNode()->createChildSceneNode();
    camera->setPosition(0, 0, 15);
    camera->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camera->attachObject(cam);

    this->setWindowGrab();

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    // finally something to render
    Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
    std::cout << "Setup!" << std::endl;
}

bool City::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    else
    {
        pressedKeys[evt.keysym.sym] = true;
    }

    return true;
}

bool City::keyReleased(const OgreBites::KeyboardEvent& evt)
{
    pressedKeys[evt.keysym.sym] = false;
    return true;
}

void City::updateCamera(Ogre::Real timeSinceLastFrame)
{
    // More or less a copy from the sample browser for free motion.
    bool mGoingForward = pressedKeys['w'];
    bool mGoingLeft = pressedKeys['a'];
    bool mGoingBack = pressedKeys['s'];
    bool mGoingRight = pressedKeys['d'];
    bool mGoingUp = pressedKeys['r'];
    bool mGoingDown = pressedKeys['f'];
    float mTopSpeed = 100;
    bool mFastMove = false;

    // build our acceleration vector based on keyboard input composite
    Ogre::Vector3 accel = Ogre::Vector3::ZERO;
    Ogre::Matrix3 axes = camera->getLocalAxes();
    if (mGoingForward) accel -= axes.GetColumn(2);
    if (mGoingBack) accel += axes.GetColumn(2);
    if (mGoingRight) accel += axes.GetColumn(0);
    if (mGoingLeft) accel -= axes.GetColumn(0);
    if (mGoingUp) accel += axes.GetColumn(1);
    if (mGoingDown) accel -= axes.GetColumn(1);

    // if accelerating, try to reach top speed in a certain time
    Ogre::Real topSpeed = mFastMove ? mTopSpeed * 20 : mTopSpeed;
    if (accel.squaredLength() != 0)
    {
        accel.normalise();
        cameraVelocity += accel * topSpeed * timeSinceLastFrame * 10;
    }
    // if not accelerating, try to stop in a certain time
    else cameraVelocity -= cameraVelocity * timeSinceLastFrame * 10;

    constexpr Ogre::Real tooSmall = std::numeric_limits<Ogre::Real>::epsilon();

    // keep camera velocity below top speed and above epsilon
    if (cameraVelocity.squaredLength() > topSpeed * topSpeed)
    {
        cameraVelocity.normalise();
        cameraVelocity *= topSpeed;
    }
    else if (cameraVelocity.squaredLength() < tooSmall * tooSmall)
        cameraVelocity = Ogre::Vector3::ZERO;

    if (cameraVelocity != Ogre::Vector3::ZERO)
        camera->translate(cameraVelocity * timeSinceLastFrame);
}

void City::frameRendered(const Ogre::FrameEvent& evt)
{
    updateCamera(evt.timeSinceLastFrame);
}

bool City::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
    camera->yaw(Ogre::Degree(-evt.xrel * 0.15f), Ogre::Node::TS_PARENT);
    camera->pitch(Ogre::Degree(-evt.yrel * 0.15f));

    return true;
}

void City::GameSetup()
{
    populace = std::unique_ptr<Population>(new Population());

    // Testing123
    populace->AddPerson();
    populace->AddPerson();
    populace->AddCompany();
    populace->Simulate();
}

int main(int argc, const char* argv)
{
	std::unique_ptr<City> city(new City());
	std::cout << "Hello World" << std::endl;

    city->initApp();
    city->GameSetup();
    std::cout << "Rendering..." << std::endl;
    city->getRoot()->startRendering();
    city->closeApp();
    return 0;
}