#pragma once
#include "vec.h"
#include <vector>

class Config {
public:
    // screen setting
    vec2 windowSize;
    float margin;

    // radius setting
    float radius;
    float closeRadius;
    float obsRadius;


    // boid setting
    int boidCount;
    float boidMoveSpeed;
    int boidLife;

    // predator setting
    int predatorCount;
    float predatorMoveSpeed;
    int predatorLife;

    // obstacle
    int obstacleCount;
    std::vector<vec4> obstacles;

public:
    Config() :
        windowSize(vec2(640, 640)),
        margin(10),

        radius(100),
        closeRadius(30),
        obsRadius(20),

        boidCount(100),
        boidMoveSpeed(50),
        boidLife(100),

        predatorCount(4),
        predatorMoveSpeed(70),
        predatorLife(80),

        obstacleCount(2)
    {
        obstacles.push_back(vec4(200, 200, 300, 300));
        obstacles.push_back(vec4(-400, -400, -200, -100));
    
    };
};
