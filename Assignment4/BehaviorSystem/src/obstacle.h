#pragma once
#include <iostream>
#include <vector>
#include "vec.h"

class Obstacle {
private:
    //vec2 bottomLeft;
    //vec2 topRight;
    vec4 bltr;
    //vec3 moveDirection;
    //float moveSpeed;

    vec4 color;

public:
    Obstacle();
    Obstacle(vec4 bltr);

    vec4 getPosition();
    
    vec2 getBottomLeft();

    vec2 getTopLeft();

    vec2 getTopRight();

    vec2 getBottomRight();

    bool isContainPoint(vec2& p);
    //vec3 getMoveDirection();
    //void setMoveDirection(const vec3& dir);

    //void update(float dt);
    void draw();

    //void move(float dt);
    //void printStats();
};