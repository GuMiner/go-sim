#pragma once
#include "OgreTerrainPagedWorldSection.h"

///Use PerlinNoise algorithm to generate terrain height map
class SinusoidalTerrainGenerator
{
public:
    SinusoidalTerrainGenerator();

    void define(Ogre::TerrainGroup* terrainGroup, long x, long y);
};
