#include <Ogre.h>
#include <OgreApplicationContext.h>

#include "Population.h"

#pragma once
class City : 
	public OgreBites::ApplicationContext,
	public OgreBites::InputListener
{
	std::unique_ptr<Population> populace;
public:
	City();
	void setup() override;
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

	void GameSetup();
};

