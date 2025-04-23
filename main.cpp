#include <iostream>
#include "raylib.h"
#include "world.h"

world newWorld = world();

int main(int, char**){
    
    InitWindow(25*64,20*64,"wave_fuction_collapse");
    
    newWorld.LoadTexturs();
    newWorld.Generate();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        newWorld.Draw();

        EndDrawing();

    }

}
