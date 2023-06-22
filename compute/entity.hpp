#pragma once
#include "vec3.hpp"
struct Entity {
    Entity() {}
    Entity(const vec3 &pos, const vec3 &vel, const double &mass) {
        this->pos = pos;
        this->vel = vel;
        this->mass = mass;
    }
    Entity(const double &x, const double &y, const double &z, const double &xVel, const double &yVel, const double &zVel, const double &mass) {
        this->pos = vec3(x, y, z);
        this->vel = vec3(xVel, yVel, zVel);
        this->mass = mass;

    }
    ~Entity() {}

    vec3 pos, vel; // distance from sun in m; orbiting velocity in m/s
    double mass; // in kg
};
