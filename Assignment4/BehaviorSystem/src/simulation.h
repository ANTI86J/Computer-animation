#pragma once
#include "config.h"
#include "creature.h"
#include "obstacle.h"
#include "behavior.h"
#include <random>
#include <vector>

class Simulation {
private:
    Config* config;
    std::vector<Boid*> boidList;
    std::vector<Predator*> predatorList;
    std::vector<Behavior*> boidBehaviorList;
    std::vector<Behavior*> predatorBehaviorList;

    std::vector<Creature*> boidBaseList;
    std::vector<Creature*> predatorBaseList;

    std::vector<Obstacle*> obstacleList;

public:
    Simulation();
    Simulation(Config* config);
    ~Simulation();

    void update(float dt);
    void draw();

    void calculateAllBoidDirections();
    void calculateAllPredatorDirections();
    //void drawBehaviorLine(vec3 dir, vec4 color, Boid& boid);
    vec3 getValidCreaturePos();
    vec3 getRandomCreaturePos();
    float getRandomLife(float life);
};