#include <iostream>
#include <memory>

#include "City.h"
#include "FlatCity.h"
#include "SinusoidalTerrainGenerator.h"

/// This class just pretends to provide procedural page content to avoid page loading
class DummyPageProvider : public Ogre::PageProvider
{
public:
    bool prepareProceduralPage(Ogre::Page* page, Ogre::PagedWorldSection* section) { return true; }
    bool loadProceduralPage(Ogre::Page* page, Ogre::PagedWorldSection* section) { return true; }
    bool unloadProceduralPage(Ogre::Page* page, Ogre::PagedWorldSection* section) { return true; }
    bool unprepareProceduralPage(Ogre::Page* page, Ogre::PagedWorldSection* section) { return true; }
};
DummyPageProvider dummyPageProvider;

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

class TerrainNoUpdateLod : public Ogre::TerrainAutoUpdateLod
{
public:
    virtual void autoUpdateLod(Ogre::Terrain* terrain, bool synchronous, const Ogre::Any& data) override
    {
        // Do nothing.
    }

    virtual Ogre::uint32 getStrategyId() { return 2; }


};

void City::configureTerrain(
    Ogre::SceneManager* sceneManager, 
    const Ogre::Light* directionalLight)
{


    Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TextureFilterOptions::TFO_ANISOTROPIC);
    Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);

#define TERRAIN_WORLD_SIZE 12000.0f
#define TERRAIN_SIZE 513
#define HOLD_LOD_DISTANCE 3000.0

#define ENDLESS_TERRAIN_FILE_PREFIX Ogre::String("EndlessWorldTerrain")
#define ENDLESS_TERRAIN_FILE_SUFFIX Ogre::String("dat")


    // max range for a int16
#define ENDLESS_PAGE_MIN_X (-0x7FFF)
#define ENDLESS_PAGE_MIN_Y (-0x7FFF)
#define ENDLESS_PAGE_MAX_X 0x7FFF
#define ENDLESS_PAGE_MAX_Y 0x7FFF

    this->terrainGroup = new Ogre::TerrainGroup(
        sceneManager, Ogre::Terrain::ALIGN_X_Z, TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
    terrainGroup->setFilenameConvention(ENDLESS_TERRAIN_FILE_PREFIX, ENDLESS_TERRAIN_FILE_SUFFIX);
    terrainGroup->setOrigin(Ogre::Vector3(0, 0, 0));
    terrainGroup->setAutoUpdateLod(new TerrainNoUpdateLod()); // Ogre::TerrainAutoUpdateLodFactory::getAutoUpdateLod(Ogre::BY_DISTANCE));
    terrainGlobals = new Ogre::TerrainGlobalOptions();

    // Configure global
    // testing composite map
    terrainGlobals->setCompositeMapDistance(3000);
    terrainGlobals->setMaxPixelError(1);
    //terrainGlobals->
    //terrainGlobals->setUseRayBoxDistanceCalculation(true);
    terrainGlobals->getDefaultMaterialGenerator()->setLightmapEnabled(true);

    terrainGlobals->setCompositeMapAmbient(sceneManager->getAmbientLight());
    terrainGlobals->setCompositeMapDiffuse(directionalLight->getDiffuseColour());
    terrainGlobals->setLightMapDirection(directionalLight->getDerivedDirection());

    // Configure default import settings for if we use imported image
    Ogre::Terrain::ImportData& defaultimp = terrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = TERRAIN_SIZE;
    defaultimp.worldSize = TERRAIN_WORLD_SIZE;
    defaultimp.inputScale = 200;
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;
    // textures

    Ogre::Image combined;
    combined.loadTwoImagesAsRGBA("Ground23_col.jpg", "Ground23_spec.png", "General");
    Ogre::TextureManager::getSingleton().loadImage("Ground23_diffspec", "General", combined);

    defaultimp.layerList.resize(3);
    defaultimp.layerList[0].worldSize = 200;
    defaultimp.layerList[0].textureNames.push_back("Ground37_diffspec.dds");
    defaultimp.layerList[0].textureNames.push_back("Ground37_normheight.dds");
    defaultimp.layerList[1].worldSize = 200;
    defaultimp.layerList[1].textureNames.push_back("Ground23_diffspec"); // loaded from memory
    defaultimp.layerList[1].textureNames.push_back("Ground23_normheight.dds");
    defaultimp.layerList[2].worldSize = 400;
    defaultimp.layerList[2].textureNames.push_back("Rock20_diffspec.dds");
    defaultimp.layerList[2].textureNames.push_back("Rock20_normheight.dds");


    SinusoidalTerrainGenerator* terrainGen = new SinusoidalTerrainGenerator();
    // worldSection->setDefiner(terrainGen);

    for (long x = 0; x <= 0; ++x)
    {
        for (long y = 0; y <= 0; ++y)
            {
            
                terrainGen->define(terrainGroup, x, y);
            }
    }
    // sync load since we want everything in place when we start
    terrainGroup->loadAllTerrains(true);
                for (const auto& ti : terrainGroup->getTerrainSlots())
                {
                    auto terrain = ti.second->instance;
                    std::cout << "LOD leves" << terrain->getNumLodLevels() << std::endl;

                    using namespace Ogre;
                    TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
                    TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
                    float minHeight0 = 20;
                    float fadeDist0 = 15;
                    float minHeight1 = 70;
                    float fadeDist1 = 15;
                    float* pBlend0 = blendMap0->getBlendPointer();
                    float* pBlend1 = blendMap1->getBlendPointer();
                    for (uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
                    {
                        for (uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
                        {
                            Real tx, ty;

                            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
                            float height = terrain->getHeightAtTerrainPosition(tx, ty);

                            *pBlend0++ = Math::saturate((height - minHeight0) / fadeDist0);
                            *pBlend1++ = Math::saturate((height - minHeight1) / fadeDist1);
                        }
                    }
                    blendMap0->dirty();
                    blendMap1->dirty();
                    blendMap0->update();
                    blendMap1->update();
                }



            Ogre::Entity* e = sceneManager->createEntity("tudorhouse.mesh");
            Ogre::Vector3 entPos(2043, 0, 1715);
            Ogre::Quaternion rot;
            entPos.y = terrainGroup->getHeightAtWorldPosition(entPos) + 65.5;
            rot.FromAngleAxis(Ogre::Degree(Ogre::Math::RangeRandom(-180, 180)), Ogre::Vector3::UNIT_Y);
            Ogre::SceneNode* sn = sceneManager->getRootSceneNode()->createChildSceneNode(entPos, rot);
            sn->setScale(Ogre::Vector3(0.12, 0.12, 0.12));
            sn->attachObject(e);
    // pageManager = new Ogre::PageManager();
    // // Since we're not loading any pages from .page files, we need a way just 
    // // to say we've loaded them without them actually being loaded
    // pageManager->setPageProvider(&dummyPageProvider);
    // pageManager->addCamera(trackingCamera);
    // pageManager->setDebugDisplayLevel(0);
    // terrainPaging = new CustomTerrainPaging(pageManager);
    // pagedWorld = pageManager->createWorld();
    // 
    // // TODO don't use a paged world section because we need to custom-modify overlays
    // // These overlays are used for resources which require us to modify on-the-fly the assigned textures.
    // CustomTerrainPagedWorldSection* worldSection = terrainPaging->createWorldSection(
    //     pagedWorld, terrainGroup, 400, 500);
    // 
    // SinusoidalTerrainGenerator* terrainGen = new SinusoidalTerrainGenerator();
    // worldSection->setDefiner(terrainGen);
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

    // TODO remove?
    scnMgr->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(0.7f, 0.7f, 0.8f), 0, 4000, 10000);

    scnMgr->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));
    scnMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");

    // also need to tell where we are
    camera = scnMgr->getRootSceneNode()->createChildSceneNode();
    camera->setPosition(0, 0, 15);
    camera->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    trackingCamera = scnMgr->createCamera("myCam");
    trackingCamera->setNearClipDistance(5); // specific to this sample
    trackingCamera->setAutoAspectRatio(true);
    camera->attachObject(trackingCamera);

    this->setWindowGrab();

    // and tell it to render into the main window
    getRenderWindow()->addViewport(trackingCamera);

    configureTerrain(scnMgr, l);

    Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
    std::cout << "Setup!" << std::endl;
}

void City::teardown()
{
    // Terrain
    //.delete terrainPaging;
    //pageManager->removeCamera(trackingCamera);
    //pageManager->destroyWorld(pagedWorld);
    //delete pageManager;
    delete terrainGroup;
    delete terrainGlobals;
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
    bool mFastMove = true;

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
    //populace->AddPerson();
    //populace->AddPerson();
    //populace->AddCompany();
    //populace->Simulate();
}

int main(int argc, const char* argv)
{
    std::unique_ptr<FlatCity> flatCity(new FlatCity());
    flatCity->Setup();
    flatCity->Run();
    flatCity->Teardown();
    return 0;

	std::unique_ptr<City> city(new City());
	std::cout << "Hello World" << std::endl;

    city->initApp();
    city->GameSetup();
    std::cout << "Rendering..." << std::endl;
    city->getRoot()->startRendering();
    city->teardown();
    city->closeApp();
    std::cout << "Exiting..." << std::endl;
    return 0;
}