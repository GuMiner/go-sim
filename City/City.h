#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreCameraMan.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <OgrePaging.h>
#include <OgreTerrainPaging.h>
#include <OgreTerrainAutoUpdateLod.h>
#include "Population.h"

#pragma once
class City : 
	public OgreBites::ApplicationContext,
	public OgreBites::InputListener
{
	Ogre::Vector3f cameraVelocity;
	Ogre::SceneNode* camera;
	void updateCamera(Ogre::Real timeSinceLastFrame);

	std::map<int, bool> pressedKeys;
	std::unique_ptr<Population> populace;

	void configureTerrain(Ogre::SceneManager* sceneManager, const Ogre::Light* directionalLight, Ogre::Camera* trackingCamera);
public:
	City();
	void setup() override;
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
	bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;

	void frameRendered(const Ogre::FrameEvent& evt) override;

	void GameSetup();
};

