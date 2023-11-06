#pragma once

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
#include <thread>
#include <chrono>
#include "declare.hpp"
#include "settings.hpp"

using namespace std;
class Quaternion;

template <typename T>
void printArray(const T& arr) {
    for (const auto& element : arr) {
        if constexpr (is_array_v<typename remove_reference<decltype(element)>::type> || is_class_v<typename remove_reference<decltype(element)>::type>) {
            // If the element is an array or class, recursively call the function
            printArray(element);
        } else {
            // Print the element (assumes the element has a suitable output operator defined)
            std::cout << element << ' ';
        }
    }
    std::cout << '\n';
}

void CheckError(int result, int errorResult, string errorMsg){
    if (result == errorResult){
        cout << "NONFATAL ERROR: " << errorMsg << endl;
        cout << "result: " << result << " error Result: " << errorResult << endl;
    }
}

void raiseErrorF(const string& msg){
    cout << "FATAL ERROR: " << msg << endl;
    exit(1);
}

bool ReadFile(const string& pFileName, string& outFile)
{
    ifstream f(pFileName);

    bool ret = false;

    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }

        f.close();

        ret = true;
    }
    else {
        raiseErrorF("file error: " + pFileName + " " + outFile);
    }

    return ret;
}

float ToRadian(float degrees){
    return degrees * (float)M_PI / 180;
}

float ToDegrees(float radians){
    return radians * (180.0f / (float) M_PI);
}

//Vector3f



Vector3f::Vector3f(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
}

void Vector3f::rotate(float Angle, const Vector3f &V) {
    Quaternion RotationQ(Angle, V);

    Quaternion ConjugateQ = RotationQ.conjugate();

    Quaternion W = RotationQ * (*this) * ConjugateQ;

    x = W.x;
    y = W.y;
    z = W.z;
}

float Vector3f::magnitude(){
    return sqrtf(x * x + y * y + z * z);
}

void Vector3f::normalize()
{
    float len = magnitude();

    assert(len != 0);

    x /= len;
    y /= len;
    z /= len;
}

Vector3f Vector3f::crossProduct(const Vector3f &v) {
    const float _x = y * v.z - z * v.y;
    const float _y = z * v.x - x * v.z;
    const float _z = x * v.y - y * v.x;

    return {_x, _y, _z};
}

ostream& operator << (ostream& os, Vector3f& v){
    os << " x: " << v.x << " y: " << v.y << " z: " << v.z;
    return os;
}

class Matrix4f{
    public:
        float matrix[4][4]{};

        Matrix4f(initializer_list<initializer_list<float>> values){
            int row = 0;
            for (const initializer_list<float>& inner_list : values) {
                int col = 0;
                for (float value : inner_list) {
                    matrix[row][col] = value;
                    col++;
                }
                row++;
            }
        }

        void assign(initializer_list<initializer_list<float>> values){
            int row = 0;
            for (const initializer_list<float>& inner_list : values) {
                int col = 0;
                for (float value : inner_list) {
                    matrix[row][col] = value;
                    col++;
                }
                row++;
            }
        }

        Matrix4f() = default;
};

class Vertex{
    public:
        Vector3f pos = Vector3f(0,0,0);
        Vector3f col = Vector3f(0,0,0);

        Vertex(float x, float y){
            pos = Vector3f(x, y, 0.0f);
        }

        Vertex(float x, float y, float z){
            pos = Vector3f(x, y, z);
            float red   = (float)rand() / (float)RAND_MAX;
            float green = (float)rand() / (float)RAND_MAX;
            float blue  = (float)rand() / (float)RAND_MAX;
            col = Vector3f(red, green, blue);
        }

        Vertex(float x, float y, float z, Vector3f _col){
            pos = Vector3f(x, y, z);
            col = _col;
        }

        Vertex() = default;
};

float distanceToNearestMultipleOf180(float x) {
    float n, m;

    if (x >= 0) {
        n = floor(x / 180.0f);
        return min(fabs(x - 180.0f * n), fabs(x - 180.0f * (n + 1)));
    } else {
        m = floor(fabs(x) / 180.0f);
        return min(fabs(x + 180.0f * m), fabs(x + 180.0f * (m + 1)));
    }
}

class Camera{
    public:
        Vector3f pos = Vector3f(0,0,0);
        float pitch = 0;
        float yaw = 0;
        bool first = true;

        explicit Camera(Vector3f _pos){
            pos = _pos;
        }

        void move(int direction){
            float facingX = cosf(yaw) / 100;
            float facingZ = sinf(yaw) / 100;
            float facingY = sinf(pitch) / 100;
            //cout << facingZ << endl;

            switch (direction){
                case (DIR_FORWARD):
                    pos.z += facingX;
                    pos.x -= facingZ;
                    pos.y += facingY;
                    break;

                case (DIR_BACK):
                    pos.z -= facingX;
                    pos.x += facingZ;
                    pos.y -= facingY;
                    break;

                case (DIR_LEFT):
                    pos.z -= facingZ;
                    pos.x -= facingX;
                    break;

                case (DIR_RIGHT):
                    pos.z += facingZ;
                    pos.x += facingX;
                    break;

                case (DIR_UP):
                    pos.y += 1.0f / 100.0f;
                    break;

                case (DIR_DOWN):
                    pos.y -= 1.0f / 100.0f;
                    break;

                default:
                    break;
            }
        }
};

class KeyMap{
    public:
        vector<int> keys;
        vector<bool> values;

        KeyMap(initializer_list<int> _keys, initializer_list<bool> _values){
            keys.reserve(_keys.size());
            values.reserve(_values.size());
            keys = _keys;
            values = _values;
        }

        bool operator[](int index){
            for (int i = 0; i < keys.size(); i++){
                if (keys[i] == index){
                    return values[i];
                    break;
                }
            }
            return false;
        }

        void assign(int index, bool state){
            for (int i = 0; i < keys.size(); i++){
                if (keys[i] == index){
                    values[i] = state;
                    break;
                }
            }
        }

        KeyMap() = default;
};

//Quaternion



Quaternion::Quaternion(float Angle, const Vector3f& V) {
    float HalfAngleInRadians = ToRadian(Angle/2);

    float SineHalfAngle = sinf(HalfAngleInRadians);
    float CosHalfAngle = cosf(HalfAngleInRadians);

    x = V.x * SineHalfAngle;
    y = V.y * SineHalfAngle;
    z = V.z * SineHalfAngle;
    w = CosHalfAngle;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w) {
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

void Quaternion::normalize() {
    float Length = sqrtf(x * x + y * y + z * z + w * w);

    x /= Length;
    y /= Length;
    z /= Length;
    w /= Length;
}

Quaternion Quaternion::conjugate() const {
    Quaternion ret(-x, -y, -z, w);
    return ret;
}

Quaternion operator*(const Quaternion& q, const Vector3f& v)
{
    float w = - (q.x * v.x) - (q.y * v.y) - (q.z * v.z);
    float x =   (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
    float y =   (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
    float z =   (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

    Quaternion ret(x, y, z, w);

    return ret;
}

Quaternion operator*(const Quaternion& l, const Quaternion& r)
{
    float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
    float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
    float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
    float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

    Quaternion ret(x, y, z, w);

    return ret;
}

void sleep(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}