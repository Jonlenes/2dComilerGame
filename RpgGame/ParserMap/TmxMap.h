#pragma once

#include <string>
#include <vector>

using namespace std;



class TmxMapTileset {
public:
    int firstGid;
    string name;
    int tileWidth;
    int tileHeight;
    string filename;
};


class TmxMapLayer {
public:
    string name;
    int width;
    int height;
    int* data;
    
    ~TmxMapLayer() {
        delete [] data;
    }
};


struct TmxMapObjectProperty {
    string name;
    string value;
};


class TmxMapObject {
public:
    string name;
    int gid;
    int x;
    int y;
    int width;
    int height;
    vector<TmxMapObjectProperty*> properties;
    
public:
    
    ~TmxMapObject() {
        for ( auto property : properties ) {
            delete property;
        }
    }
};


class TmxMapObjectGroup {
public:
    string name;
    int width;
    int height;
    bool visible;
    
    vector<TmxMapObject*> objects;
    
    ~TmxMapObjectGroup() {
        for ( auto o : objects ) {
            delete o;
        }
    }
};


class TmxMap {
public:

    static TmxMap *loadTmxMap( char *xml );
    
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    
    vector<TmxMapTileset*> tilesets;
    vector<TmxMapLayer*> layers;
    vector<TmxMapObjectGroup*> groups;
    
    ~TmxMap() {
        for ( auto g : groups ) {
            delete g;
        }
        
        for ( auto l : layers ) {
            delete l;
        }
        
        for ( auto ts : tilesets ) {
            delete ts;
        }
    }
    
    
};

