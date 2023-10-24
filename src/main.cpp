#pragma once

#include "raylib.h"
#include <stdio.h>
#include <iostream>
#include "cube.hpp"

using namespace std;

//predef
void draw();
class TexturedCube;

int keyConvert(char key){
    return (int) key;
}



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Load textures for each face of the cube
    Texture2D tex1 = LoadTexture("../assets/textures/blocks/stone.png");
    Texture2D tex2 = LoadTexture("../assets/textures/blocks/deepslate.png");

    Texture2D faces[6] = {tex1, tex2, tex1, tex2, tex1, tex2};
    TexturedCube c1 = TexturedCube((Vector3){1,1,1}, 1, faces);
    c1.init();

    DisableCursor();            

    SetTargetFPS(60);            
    while (!WindowShouldClose())
    {
        if (IsKeyDown(89)) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        BeginDrawing();

            UpdateCamera(&camera, CAMERA_FREE);

            ClearBackground(BLACK);

            BeginMode3D(camera);
                //draw stuff
                c1.draw();

            EndMode3D();

            DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 133, BLUE);

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
            DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}