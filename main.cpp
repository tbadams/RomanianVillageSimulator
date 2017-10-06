#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "WorldMap.h"

using namespace std;

class Village : public Place {
public:
    Village(int xCoord,int yCoord):Place(xCoord,yCoord) {}

};



class VillageFactory {
public:
    VillageFactory(WorldMap* worldMap) {
        theMap = worldMap;
    }
private:
    int seed = -1;
    WorldMap* theMap;
    public:
    Village * build();
};

Village* VillageFactory::build() {
    int curSeed = seed >= 0 ? seed : time(NULL); // Use seed if provided, else random
    return new Village(0,0);
}

int main()
{
    cout << "BEGIN PROGRAM" << endl;
    WorldMap theMap (3600, 3600);
    VillageFactory villageFactory (&theMap);
    Village *village = villageFactory.build();
    cout << village->toString() << endl;
    //cin >> age;
    return 0;
}
