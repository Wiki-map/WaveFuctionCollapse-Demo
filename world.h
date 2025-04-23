#pragma once
#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <queue>
#include <set>
#include <iostream>
#include <bitset>
#include <time.h>

class world {
private:
    
    const int tilesize = 64;
    const int width = 20*64;
    const int height = 25*64;
    const int GRASS = 1;
    const int SAND = 2;
    const int WATER = 3;
    const int TREES = 4;


    /*
        so my first ideea was to implement wave fuction collapse
        with a list of posibilities for every position in the tiles matrix
        but i realized that you can use prime numbers to simulate the same thing
        and just multiply them.

        this works well on a small data sets but with more tiles this 
        can be a problem.


        EDIT: i was so dumb, i just implemented it with bitset
    */

    Texture2D worldTexturs[5];
    bool Rules[4][4] = {{1,1,0,1},{1,1,1,0},{0,1,1,0},{1,0,0,1}};
    std::vector<std::vector<std::bitset<5>>> tiles;

public:
    world();
    void LoadTexturs();
    void Generate();
    void Draw();
};
