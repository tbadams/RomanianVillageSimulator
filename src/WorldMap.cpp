#include "WorldMap.h"

Place::Place(int xCoord, int yCoord)
{
    x = xCoord;
    y = yCoord;
}

std::string Place::toString()
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

WorldMap::WorldMap(int mapWidth, int mapHeight)
{
    width = mapWidth;
    height = mapHeight;
}

WorldMap::~WorldMap()
{
    //dtor
}


