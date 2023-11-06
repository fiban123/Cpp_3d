#pragma once

#include "../dependencies/include/glew/glew.h"
#include "../dependencies/include/freeglut/glut.h"
#include <cmath>
#include <string>

#define KEY_ESCAPE 27
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_Q 113
#define KEY_E 101
#define KEY_R 114
#define KEY_SPACE 32
#define SKEY_UP 101
#define SKEY_LEFT 100
#define SKEY_DOWN 103
#define SKEY_RIGHT 102
#define SKEY_SHIFT 112
#define DIR_FORWARD 0
#define DIR_BACK 1
#define DIR_LEFT 2
#define DIR_RIGHT 3
#define DIR_UP 4
#define DIR_DOWN 5

//include this after the macros bc util.hpp requres these macros
#include "util.hpp"


GLuint VBO;
GLuint IBO;
GLint rotationLocation;
GLint scalingLocation;
GLint projectionLocation;
GLint translationLocation;
GLint cameraLocation;
GLint cameraRotationHMatrixLocation;
GLint cameraRotationVMatrixLocation;
GLint cameraPosLocation;

static int width = 1920;
static int height = 1080;

KeyMap keysPressed(
        {KEY_W, KEY_A, KEY_S, KEY_D, KEY_Q, KEY_E, KEY_SPACE},
        {false, false, false, false, false, false, false});

KeyMap specialKeysPressed(
        {SKEY_UP, SKEY_DOWN, SKEY_LEFT, SKEY_RIGHT, SKEY_SHIFT},
        {false, false, false, false, false});

static float angleRadians = 0;
static float scale = 0.7;
static float FOV = 70;
static float cameraMovementSpeed = 0.01;
static long double nearPlane = 0.01;
static long double farPlane = 10000;
static Vector3f cameraStartPos(0,0,0);



Matrix4f rotationMatrix;
Matrix4f scalingMatrix;
Matrix4f cameraMatrix;
Matrix4f cameraRotationHMatrix;
Matrix4f cameraRotationVMatrix;

static float f = 1 / tanf(ToRadian(FOV / 2.0f));
static float aspectRatio =  (float) width / (float)  height;
static long double planeRange = farPlane - nearPlane;
static long double A = (-farPlane - nearPlane) / planeRange;
static long double B = 2.0f * farPlane * nearPlane / planeRange;

Matrix4f projectionMatrix({
          {f / aspectRatio, 0, 0, 0},
          {0, f, 0, 0},
          {0, 0, (float) A, (float) B},
          {0, 0, 1, 0}});

Matrix4f translationMatrix({
          {1, 0, 0, 0},
          {0, 1, 0, 0},
          {0, 0, 1, 1},
          {0, 0, 0, 1}});

Camera camera(cameraStartPos);

const string gamemodeString = to_string(width) + "x" + to_string(height) + "@60";