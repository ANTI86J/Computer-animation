#pragma once
#include "creature.h"
#include "obstacle.h"
#include "vec.h"
#include <vector>

class Behavior {
public:
    float weight = 0;
    std::vector<Creature*>* context;
    virtual vec3 calculateMoveDirection(Creature& boid, const std::vector<Obstacle*> &obs) = 0;
    Behavior(float weight, std::vector<Creature*>* context);
};

class Alignment : public Behavior {
public:
    Alignment(float weight, float radius, std::vector<Creature*>* context);
    vec3 calculateMoveDirection(Creature& boid, const std::vector<Obstacle*> &obs) override;
private:
    float radius;
};

class Cohesion : public Behavior {
public:
    Cohesion(float weight, float radius, std::vector<Creature*>* context);
    vec3 calculateMoveDirection(Creature& boid, const std::vector<Obstacle*>& obs) override;
private:
    float radius;
};

class Separation : public Behavior {
public:
    Separation(float weight, float radius, std::vector<Creature*>* context);
    vec3 calculateMoveDirection(Creature& boid, const std::vector<Obstacle*>& obs) override;
private:
    float radius;
};

class AvoidObs : public Behavior {
public:
    enum LinePos
    {
        NONE,
        BOTTOM,
        LEFT,
        RIGHT,
        TOP
    };
    AvoidObs(float weight, float radius, std::vector<Creature*>* context);
    vec3 calculateMoveDirection(Creature& boid, const std::vector<Obstacle*>& obs) override;
private:
    bool updateIntersectDist(const vec2& start, const vec2& end, const vec2& ls, const vec2& le, float* distance, vec2* intersect_point);
    float radius;
};

class Prey : public Behavior {
public:
    Prey(float weight, float radius, std::vector<Creature*>* context);
    vec3 calculateMoveDirection(Creature& boid, const std::vector<Obstacle*>& obs) override;
private:
    float radius;
};