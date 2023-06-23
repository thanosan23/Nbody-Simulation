#pragma once
#include <iostream>

struct vec3 {
    vec3() {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
    }
    vec3(const double &pX, const double &pY, const double &pZ) {
        this->x = pX;
        this->y = pY;
        this->z = pZ;
    }
    vec3(const double &pVal) {
        this->x = pVal;
        this->y = pVal;
        this->z = pVal;
    }
    ~vec3() {}

    double mag() {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    vec3 unit() {
        return vec3(this->x/this->mag(), this->y/this->mag(), this->z/this->mag());
    }

    vec3 operator*(const float &scalar) {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

    vec3 operator+(const vec3 &other) {
        return vec3(x + other.x, y + other.y, z + other.z);
    }

    vec3 operator-(const vec3 &other) {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    vec3 operator*(const vec3 &other) {
        return vec3(x * other.x, y * other.y, z * other.z);
    }

    vec3 operator/(const vec3 &other) {
        return vec3(x / other.x, y / other.y, z / other.z);
    }

    void operator*=(const vec3 &other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }

    void operator/=(const vec3 &other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }

     void operator+=(const vec3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    void operator-=(const vec3 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    double x, y, z;
};
