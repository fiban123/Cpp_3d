#pragma once

#include "../dependencies/include/glew/glew.h"
#include "../dependencies/include/freeglut/glut.h"
#include "settings.hpp"
#include "render.hpp"
#include "util.hpp"
#include <cmath>
#include <iostream>

static void OnKeyboard(int key, bool keyState, bool special){
    key = (int) key;
    if(key == KEY_ESCAPE){
        glutDestroyWindow(1);
        exit(1);
    }
    if(key == KEY_R){
        camera.pitch = 0;
        camera.yaw = 0;
    }
    if (!special){
        for (int i = 0; i < keysPressed.keys.size(); i++){
            int cKey = keysPressed.keys[i];
            if (cKey == key){
                keysPressed.assign(cKey, keyState);
            }
        }
    }
    else{
        for (int i = 0; i < specialKeysPressed.keys.size(); i++){
            int cKey = specialKeysPressed.keys[i];
            if (cKey == key){
                specialKeysPressed.assign(cKey, keyState);
            }
        }
    }
    //cout << (char) key << " " << (int) key << endl;
}

static void Keyboard(unsigned char key, int mousex, int mousey){
    OnKeyboard(key, true, false);
    //cout << (char) key << " " << (int) key << endl;
}

static void SpecialKeyboard(int key, int mousex, int mousey){
    OnKeyboard(key, true, true);
    //cout << "special " << (char) key << " " << (int) key << endl;
}

static void KeyboardUp(unsigned char key, int mousex, int mousey){
    OnKeyboard(key, false, false);
}

static void SpecialKeyboardUp(int key, int mousex, int mousey){
    OnKeyboard(key, false, true);
}

static void PassiveMouse(int x, int y){
    int deltaX = x - width / 2;
    int deltaY = y - height / 2;

    glutWarpPointer(width / 2,height / 2);

    if (camera.first){
        camera.pitch -= ((float) deltaY) / 100;
        camera.yaw -= ((float) deltaX) / 100;
    }
    else{
        camera.first = true;
        camera.pitch = 0;
        camera.yaw = 0;
    }

};

void UpdateKeyboard(){
    if (specialKeysPressed[SKEY_SHIFT]){
        camera.move(DIR_DOWN);
    }

    if (keysPressed[KEY_SPACE]){
        camera.move(DIR_UP);
    }

    if (keysPressed[KEY_A]){
        camera.move(DIR_LEFT);
    }

    if (keysPressed[KEY_D]){
        camera.move(DIR_RIGHT);
    }

    if (keysPressed[KEY_S]){
        camera.move(DIR_BACK);
    }

    if (keysPressed[KEY_W]){
        camera.move(DIR_FORWARD);
    }

    if (specialKeysPressed[SKEY_UP]){
        camera.pitch += 0.01f;
    }

    if (specialKeysPressed[SKEY_DOWN]){
        camera.pitch -= 0.01f;
    }

    if (specialKeysPressed[SKEY_RIGHT]){
        camera.yaw += 0.01f;
    }

    if (specialKeysPressed[SKEY_LEFT]){
        camera.yaw -= 0.01f;
    }
}