#pragma once
#include "OgreTerrainPagedWorldSection.h"

///Use PerlinNoise algorithm to generate terrain height map
class SinusoidalTerrainGenerator : public Ogre::TerrainPagedWorldSection::TerrainDefiner
{
public:
    SinusoidalTerrainGenerator();

    virtual void define(Ogre::TerrainGroup* terrainGroup, long x, long y) override;
};
