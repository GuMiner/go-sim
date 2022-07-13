#include "SinusoidalTerrainGenerator.h"
#include <stdlib.h>
#include <math.h>
#include "OgreMath.h"


SinusoidalTerrainGenerator::SinusoidalTerrainGenerator()
{
}

void SinusoidalTerrainGenerator::define(
    Ogre::TerrainGroup* terrainGroup, long x, long y)
{
    Ogre::uint16 terrainSize = terrainGroup->getTerrainSize();
    float* heightMap = new float[
        (terrainSize * terrainSize) * sizeof(Ogre::MEMCATEGORY_GEOMETRY)];

    Ogre::Vector2 worldOffset(
        Ogre::Real(x * (terrainSize - 1)),
        Ogre::Real(y * (terrainSize - 1)));
    // worldOffset += mOriginPoint;

    Ogre::Vector2 revisedValuePoint;
    for (Ogre::uint16 i = 0; i < terrainSize; i++)
        for (Ogre::uint16 j = 0; j < terrainSize; j++)
        {
            revisedValuePoint = (worldOffset + Ogre::Vector2(j, i));
            heightMap[i * terrainSize + j] = (float)(sin(0.05f * (float)revisedValuePoint.x)*cos(0.05f * revisedValuePoint.y));
        }
    terrainGroup->defineTerrain(x, y, heightMap);
    delete[] heightMap;
}