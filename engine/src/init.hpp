#pragma once

#include "../dependencies/include/glew/glew.h"
#include "../dependencies/include/freeglut/glut.h"
#include "settings.hpp"
#include "render.hpp"
#include "util.hpp"
#include "keyboard.hpp"


static void CreateIndexBuffer(){
    unsigned int cubeIndices[] = {
            0, 1, 2,
            1, 3, 4,
            5, 6, 3,
            7, 3, 6,
            2, 4, 7,
            0, 7, 6,
            0, 5, 1,
            1, 5, 3,
            5, 0, 6,
            7, 4, 3,
            2, 1, 4,
            0, 2, 7
    };

    vector<unsigned int> indices;
    int nCubeIndices = 36;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < nCubeIndices; j++){
            indices.emplace_back(8 * i + cubeIndices[j % nCubeIndices]);
        }
    }

    unsigned int indicesArray[indices.size()];
    cout << "indices: " << endl << endl;
    for (int i = 0; i < indices.size(); i++){
        indicesArray[i] = indices[i];
        cout << indices[i] << " ";
    }
    cout << endl;

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indicesArray, GL_STATIC_DRAW);
}

static void CreateVertexBuffer()
{
    vector<Vertex> vertices;

    Vector3f cubes[4] = {
            Vector3f(5, 0, 0),
            Vector3f(0, 0, 5),
            Vector3f(-5, 0, 0),
            Vector3f(0, 0, -5)
    };

    for (Vector3f i : cubes){
        vertices.emplace_back(i.x + 0.5f, i.y + 0.5f, i.z + 0.5f);
        vertices.emplace_back(i.x + -0.5f, i.y + 0.5f, i.z + -0.5f);
        vertices.emplace_back(i.x + -0.5f, i.y + 0.5f, i.z + 0.5f);
        vertices.emplace_back(i.x + 0.5f, i.y + -0.5f, i.z + -0.5f);
        vertices.emplace_back(i.x + -0.5f, i.y + -0.5f, i.z + -0.5f);
        vertices.emplace_back(i.x + 0.5f, i.y + 0.5f, i.z + -0.5f);
        vertices.emplace_back(i.x + 0.5f, i.y + -0.5f, i.z + 0.5f);
        vertices.emplace_back(i.x + -0.5f, i.y + -0.5f, i.z + 0.5f);
    }

    Vertex verticeArray[vertices.size()];
    cout << "Vertices: " << endl << endl;
    for (int i = 0; i < vertices.size(); i++){
        verticeArray[i] = vertices[i];
        cout << vertices[i].pos.x << " " << vertices[i].pos.y << " " << vertices[i].pos.z << endl;
    }
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), verticeArray, GL_STATIC_DRAW);
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);
    CheckError(ShaderObj, 0, "Error creating shader type");

    const GLchar* p[1];
    p[0] = pShaderText;

    GLint Lengths[1];
    Lengths[0] = (GLint)strlen(pShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        cout << "shader error 1" << endl;
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

const char* pVSFileName = "src/shaderv.fs";
const char* pFSFileName = "src/shader.fs";

static void addLocations(GLuint shaderProgram){
    rotationLocation = glGetUniformLocation(shaderProgram, "rotationMatrix");
    CheckError(rotationLocation, -1, "failed to add uniform variable 1");

    scalingLocation = glGetUniformLocation(shaderProgram, "scalingMatrix");
    CheckError(scalingLocation, -1, "failed to add uniform variable 2");

    projectionLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    CheckError(projectionLocation, -1, "failed to add uniform variable 3");

    translationLocation = glGetUniformLocation(shaderProgram, "translationMatrix");
    CheckError(translationLocation, -1, "failed to add uniform variable 4");

    cameraLocation = glGetUniformLocation(shaderProgram, "cameraMatrix");
    CheckError(cameraLocation, -1, "failed to add uniform variable 5");

    cameraRotationHMatrixLocation = glGetUniformLocation(shaderProgram, "cameraRotationHMatrix");
    CheckError(cameraRotationHMatrixLocation, -1, "failed to add uniform variable 6");

    cameraRotationVMatrixLocation = glGetUniformLocation(shaderProgram, "cameraRotationVMatrix");
    CheckError(cameraRotationVMatrixLocation, -1, "failed to add uniform variable 7");

    cameraPosLocation = glGetUniformLocation(shaderProgram, "cameraPos");
    CheckError(cameraPosLocation, -1, "failed to add uniform variable 8");
}

static void CompileShaders()
{
    GLuint shaderProgram = glCreateProgram();

    if (shaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    std::string vs, fs;

    if (!ReadFile(pVSFileName, vs)) {
        exit(1);
    };

    AddShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);

    if (!ReadFile(pFSFileName, fs)) {
        exit(1);
    };

    AddShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Success);


    if (Success == 0) {
        glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), nullptr, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    addLocations(shaderProgram);

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), nullptr, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(shaderProgram);
}

void initWindow(int argc, char** argv){
    //initialize stuff
    srand(getpid());
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    int win = glutCreateWindow("hi idk");

    glutDisplayFunc(render);
    //glutGameModeString(gamemodeString.c_str());
    //glutEnterGameMode();

    glutDisplayFunc(render);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyboard);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialUpFunc(SpecialKeyboardUp);
    glutPassiveMotionFunc(PassiveMouse);

    GLenum res = glewInit();
    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;

    glClearColor(Red, Green, Blue, Alpha);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    CreateVertexBuffer();
    CreateIndexBuffer();
    CompileShaders();
}