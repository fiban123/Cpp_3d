#pragma once

#include "../dependencies/include/glew/glew.h"
#include "../dependencies/include/freeglut/glut.h"
#include "settings.hpp"
#include "render.hpp"
#include "util.hpp"
#include "keyboard.hpp"
#include <cmath>
#include <iostream>


static void render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    UpdateKeyboard();

    //angleRadians += 0.0012f;
    //scale += 0.0005f;

    scalingMatrix.assign({
         {scale, 0, 0, 0},
         {0, scale, 0, 0},
         {0, 0, scale, 0},
         {0, 0, 0, 1}
    });

    rotationMatrix.assign({
        {cosf(angleRadians), 0, -sinf(angleRadians), 0},
        {0, 1, 0, 0},
        {sinf(angleRadians), 0, cosf(angleRadians), 0},
        {0, 0, 0, 1}
    });

    cameraMatrix.assign({
        {1, 0, 0, -camera.pos.x},
        {0, 1, 0, -camera.pos.y},
        {0, 0, 1, -camera.pos.z},
        {0, 0, 0, 1}
    });

    cameraRotationVMatrix.assign({
         {1, 0,                  0,                   0},
         {0, cosf(camera.pitch), -sinf(camera.pitch), 0},
         {0, sinf(camera.pitch), cosf(camera.pitch),  0},
         {0, 0,                  0,                   1}
    });

    cameraRotationHMatrix.assign({
         {cosf(camera.yaw),  0, sinf(camera.yaw), 0},
         {0,                 1, 0,                0},
         {-sinf(camera.yaw), 0, cosf(camera.yaw), 0},
         {0,                 0, 0,                1}
    });


    //cout << camera.yaw << "  " << camera.pitch << endl;
    //cout << camera.pos << " " << ToDegrees(camera.pitch) << " " << ToDegrees(camera.yaw) << endl;

    glUniformMatrix4fv(rotationLocation, 1, GL_TRUE, &rotationMatrix.matrix[0][0]);
    glUniformMatrix4fv(scalingLocation, 1, GL_TRUE, &scalingMatrix.matrix[0][0]);
    glUniformMatrix4fv(projectionLocation, 1, GL_TRUE, &projectionMatrix.matrix[0][0]);
    glUniformMatrix4fv(translationLocation, 1, GL_TRUE, &translationMatrix.matrix[0][0]);
    glUniformMatrix4fv(cameraLocation, 1, GL_TRUE, &cameraMatrix.matrix[0][0]);
    glUniformMatrix4fv(cameraRotationVMatrixLocation, 1, GL_TRUE, &cameraRotationVMatrix.matrix[0][0]);
    glUniformMatrix4fv(cameraRotationHMatrixLocation, 1, GL_TRUE, &cameraRotationHMatrix.matrix[0][0]);
    glUniform3f(cameraPosLocation, camera.pos.x, camera.pos.y, camera.pos.z);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    //pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);

    //col
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, 36 * 4, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glutPostRedisplay();

    glutSwapBuffers();
}