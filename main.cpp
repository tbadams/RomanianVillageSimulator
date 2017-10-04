#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "WorldMap.h"

using namespace std;

class Village : public Place {
//public:
//    Village(int,int):Place(int,int);

};

//Village::Village(int xCoord, yCoord) {
//}

class VillageFactory {
    public:
    Village * build();
};

Village* VillageFactory::build() {
    return new Village;
}

int main()
{
    cout << "BEGIN PROGRAM" << endl;
    WorldMap map (3600, 3600);
    VillageFactory villageFactory;
    Village *village = villageFactory.build();
    //cin >> age;
    return 0;
}
