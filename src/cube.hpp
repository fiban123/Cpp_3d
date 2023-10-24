#pragma once

#include "raylib.h"
#include "main.cpp"

/*top, bottom, left, right, front, back*/
class TexturedCube{
    private:
        Model models[6];

        Material materials[6] = {
                LoadMaterialDefault(), LoadMaterialDefault(), LoadMaterialDefault(),
                LoadMaterialDefault(), LoadMaterialDefault(), LoadMaterialDefault()
    };

        Vector3 positions[6] = {
                (Vector3){0, 0.5, 0},
                (Vector3){0, -0.5, 0},
                (Vector3){0, 0, 0.5},
                (Vector3){0, 0, -0.5},
                (Vector3){0.5, 0, 0},
                (Vector3){-0.5, 0, 0}
        };

        Vector3 rotationAxis[6] = {
                (Vector3){0, 0, 0},
                (Vector3){90, 0, 0},
                (Vector3){90, 0, 0},
                (Vector3){90, 0, 0},
                (Vector3){0, 0, 90},
                (Vector3){0, 0, 90},
        };

        float rotationAngles[6] = {0,180,90,-90,-90,90};

    public:
        Vector3 center;
        float size;
        Texture2D faces[6];

        TexturedCube(Vector3 center2, float size2, Texture2D faces2[6]){
            center = center2;
            size = size2;
            for (int i = 0; i < 6; i++) {
                faces[i] = faces2[i];
            }
        }
        void draw(){
           for (int i = 0; i < 6; i++){
                DrawModelEx(models[i], positions[i], rotationAxis[i], rotationAngles[i],(Vector3){1,1,1}, WHITE);
           }
        }

        void init(){

            for (int i = 0; i < 6; i++){
                materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = faces[i];
                models[i] = LoadModelFromMesh(GenMeshPlane(size, size, 1, 1));
                models[i].materials[0] = materials[i];
            }
        }
};