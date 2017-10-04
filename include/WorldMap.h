#ifndef WORLDMAP_H
#define WORLDMAP_H
#include <unordered_map>

class Place {
private:
    int x,y;
public:
//    Place();
//    Place(int,int);
    int getX() {
    return x;}
    int getY();
};

class WorldMap
{
    public:
        WorldMap(int,int);
        virtual ~WorldMap();
        void add(Place place);
    protected:
    private:
        int width, height;
};



#endif // WORLDMAP_H
