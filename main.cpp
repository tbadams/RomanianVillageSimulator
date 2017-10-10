#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cursesapp.h>
#include <cursesm.h>
#include <cursesf.h>

#include "WorldMap.h"

using namespace std;

class Village : public Place {
public:
    Village(int xCoord,int yCoord):Place(xCoord,yCoord) {}
    // Todo width, height

};



class VillageFactory {
public:
    VillageFactory(WorldMap* worldMap, int seed) {
        theMap = worldMap;
        int curSeed = seed >= 0 ? seed : time(NULL); // Use seed if provided, else random
        srand(curSeed);
    }
private:
    WorldMap* theMap;
    public:
    Village * build();
};

Village* VillageFactory::build() {

    return new Village(rand() % (theMap->getWidth()-1), rand() % (theMap->getHeight()-1));
}

int main()
{
    cout << "BEGIN PROGRAM" << endl;
    WorldMap theMap (3600, 3600);
    VillageFactory villageFactory (&theMap, -1);
    Village *village = villageFactory.build();
    cout << village->toString() << endl;
    //cin >> age;
    return 0;
}
