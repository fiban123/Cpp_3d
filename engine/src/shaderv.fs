#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 inColor;

uniform mat4 rotationMatrix;
uniform mat4 scalingMatrix;
uniform mat4 projectionMatrix;
uniform mat4 translationMatrix;
uniform mat4 cameraMatrix;
uniform mat4 cameraRotationHMatrix;
uniform mat4 cameraRotationVMatrix;
uniform vec3 cameraPos;

out vec4 color;

mat4 rotationX;
vec4 tmp;

vec4 rotateAroundOrigin(vec4 point, vec4 origin){
    vec4 translated = point - origin;
    translated = cameraRotationHMatrix * translated;
    translated = cameraRotationVMatrix * translated;
    return translated + origin;
}

void main()
{
    mat4 tmp = projectionMatrix * cameraMatrix;
    vec4 tmp2 = tmp * rotateAroundOrigin(vec4(Position, 1.0), vec4(cameraPos, 0));
    gl_Position = tmp2;
    //gl_Position = mvp * vec4(Position, 1);
    color = vec4(inColor, 1.0f);
}