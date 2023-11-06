#include <iostream>

using namespace std;

class Vector3f{
public:

    float x{};
    float y{};
    float z{};

    Vector3f(float _x, float _y, float _z);

    void rotate(float Angle, const Vector3f& V);

    void normalize();

    Vector3f crossProduct(const Vector3f& v);

    Vector3f() = default;

    float magnitude();
};

ostream& operator << (ostream& os, Vector3f& v);


class Quaternion{
    public:
        float x = 0;
        float y = 0;
        float z = 0;
        float w = 0;

        Quaternion(float Angle, const Vector3f& V);

        Quaternion(float _x, float _y, float _z, float _w);

        void normalize();

        Quaternion conjugate() const;

        Quaternion() = default;
};

Quaternion operator*(const Quaternion& l, const Vector3f& r);
Quaternion operator*(const Quaternion& l, const Quaternion& r);