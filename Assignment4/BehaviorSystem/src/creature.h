#pragma once
#include <iostream>
#include <vector>
#include "vec.h"

class Creature {
private:
    vec3 position;
    vec3 moveDirection;
    float moveSpeed;
    float life;

    float size;
    vec4 color;

    bool dead;
public:
    Creature();
    Creature(vec3 position, vec3 moveDirection, float moveSpeed, float life, float size, vec4 color);

    vec3 getPosition();
    vec3 getMoveDirection();
    void setMoveDirection(const vec3& dir);

    bool isDead();
    void setDead(bool v);

    void update(float dt);
    void draw();

    void fade(float dt);
    void move(float dt);
    void printStats();
};


class Boid : public Creature {
public:
    Boid(vec3 position, vec3 moveDirection, float moveSpeed, float life) : Creature(position, moveDirection, moveSpeed, life, 10, vec4(1,1,1,1)) {};
};

class Predator : public Creature {
public:
    Predator(vec3 position, vec3 moveDirection, float moveSpeed, float life) : Creature(position, moveDirection, moveSpeed, life, 20, vec4(0,0,1,1)) {};
    void prey(Creature& creature);
};