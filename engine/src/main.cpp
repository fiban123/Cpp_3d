#include <iostream>
#include "../dependencies/include/glew/glew.h"
#include "../dependencies/include/freeglut/glut.h"
#include "init.hpp"

using namespace std;


int main(int argc, char** argv){
    cout << "start" << endl;

    initWindow(argc, argv);

    glutMainLoop();

    return 0;
}