#include "simulation.h"

extern vec2 windowSize;
Simulation::Simulation() {}

Simulation::Simulation(Config* config) {
    this->config = config;
    boidList = std::vector<Boid*>();
    boidBaseList = std::vector<Creature*>();
    predatorList = std::vector<Predator*>();
    predatorBaseList = std::vector<Creature*>();
    obstacleList = std::vector<Obstacle*>();

    // 1. boundry
    // left
    obstacleList.push_back(new Obstacle(vec4(-windowSize.x - config->margin, -windowSize.y, -windowSize.x + config->margin, windowSize.y)));
    // right
    obstacleList.push_back(new Obstacle(vec4(windowSize.x - config->margin, -windowSize.y, windowSize.x + config->margin, windowSize.y)));
    // bottom
    obstacleList.push_back(new Obstacle(vec4(-windowSize.x, -windowSize.y - config->margin, windowSize.x, -windowSize.y + config->margin)));
    // bottom
    obstacleList.push_back(new Obstacle(vec4(-windowSize.x, windowSize.y - config->margin, windowSize.x, windowSize.y + config->margin)));


    // 2. obstacles list
    for (auto obs : config->obstacles) {
        obstacleList.push_back(new Obstacle(obs));
    }


    // 3. boid list
    for(int i = 0; i < config->boidCount; i++) {
        vec3 pos = getValidCreaturePos();
        vec3 moveDir = vec3(0,1,0);
        float moveSpeed = config->boidMoveSpeed;
        //  80% - 120% average life time
        float life = getRandomLife(config->boidLife);
        this->boidList.push_back(new Boid(pos, moveDir, moveSpeed, life));
    }

    // 4. predator list
    for (int i = 0; i < config->predatorCount; i++) {
        vec3 pos = getValidCreaturePos();
        vec3 moveDir = vec3(0, 1, 0);
        float moveSpeed = config->predatorMoveSpeed;
        //  80% - 120% average life time
        float life = getRandomLife(config->predatorLife);
        this->predatorList.push_back(new Predator(pos, moveDir, moveSpeed, life));
    }

    for (auto boid : boidList) {
        boidBaseList.push_back(dynamic_cast<Creature*>(boid));
    }
    for (auto predator : predatorList) {
        predatorBaseList.push_back(dynamic_cast<Creature*>(predator));
    }


    // 5. boid behavior
    boidBehaviorList = std::vector<Behavior*>();
    boidBehaviorList.push_back(new Cohesion(9, config->radius, &boidBaseList));
    boidBehaviorList.push_back(new Alignment(4, config->radius, &boidBaseList));
    boidBehaviorList.push_back(new Separation(12, config->closeRadius, &boidBaseList));
    // avoid predator
    boidBehaviorList.push_back(new Separation(20, config->radius, &predatorBaseList));
    //boidBehaviorList.push_back(new AvoidObs(50, obsRadius, nullptr));

    // 6. predator behavior
    predatorBehaviorList = std::vector<Behavior*>();
    predatorBehaviorList.push_back(new Separation(12, config->closeRadius, &predatorBaseList));
    predatorBehaviorList.push_back(new Cohesion(9, config->radius, &boidBaseList));
    predatorBehaviorList.push_back(new Prey(0, 0.5 * config->closeRadius, &boidBaseList));
    //predatorBehaviorList.push_back(new AvoidObs(80, obsRadius, nullptr));
}

Simulation::~Simulation() {
    for(std::vector<Boid*>::iterator it = boidList.begin(); it != boidList.end(); ) {
        delete (*it);
        it = boidList.erase(it);
    }
    for(std::vector<Behavior*>::iterator it = boidBehaviorList.begin(); it != boidBehaviorList.end(); ) {
        delete (*it);
        it = boidBehaviorList.erase(it);
    }
    for (std::vector<Predator*>::iterator it = predatorList.begin(); it != predatorList.end(); ) {
        delete (*it);
        it = predatorList.erase(it);
    }
    for (std::vector<Behavior*>::iterator it = predatorBehaviorList.begin(); it != predatorBehaviorList.end(); ) {
        delete (*it);
        it = predatorBehaviorList.erase(it);
    }
    for (std::vector<Obstacle*>::iterator it = obstacleList.begin(); it != obstacleList.end(); ) {
        delete (*it);
        it = obstacleList.erase(it);
    }
    for (std::vector<Creature*>::iterator it = boidBaseList.begin(); it != boidBaseList.end(); ) {
        delete (*it);
        it = boidBaseList.erase(it);
    }
    for (std::vector<Creature*>::iterator it = predatorBaseList.begin(); it != predatorBaseList.end(); ) {
        delete (*it);
        it = predatorBaseList.erase(it);
    }
}

void Simulation::update(float dt) {
    calculateAllBoidDirections();
    calculateAllPredatorDirections();
    for (auto boid : boidList) {
        boid->update(dt);
    }
    for (auto predator : predatorList) {
        predator->update(dt);
    }
}

void Simulation::draw() {
    for(auto boid : boidList) {
        boid->draw();
    }
    for (auto predator : predatorList) {
        predator->draw();
    }
    for (auto obs : obstacleList) {
        obs->draw();
    }
}

void Simulation::calculateAllBoidDirections() {
    for(auto it_boid = boidList.begin(); it_boid != boidList.end(); it_boid++) {
        vec3 moveDirection = vec3();

        for(auto it_bhv = boidBehaviorList.begin(); it_bhv != boidBehaviorList.end(); it_bhv++) {
            moveDirection += (*it_bhv)->calculateMoveDirection(**it_boid, obstacleList) * (*it_bhv)->weight;
            if(isnan(moveDirection.x) || isnan(moveDirection.y) || isnan(moveDirection.z)) {
                std::cout << "FOUND NAN" << std::endl;
                exit(0);
            }
        }

        // avoid obstabcle is a hard rule
        AvoidObs bhv(0, config->obsRadius, nullptr);
        vec3 direction = bhv.calculateMoveDirection(**it_boid, obstacleList);
        if (direction.magnitude() != 0) {
            moveDirection = direction * moveDirection.magnitude() * 2;
        }
        (*it_boid)->setMoveDirection(moveDirection);
    }
}

void Simulation::calculateAllPredatorDirections(){
    for (auto it_predator = predatorList.begin(); it_predator != predatorList.end(); it_predator++) {
        vec3 moveDirection = vec3();

        for (auto it_bhv = predatorBehaviorList.begin(); it_bhv != predatorBehaviorList.end(); it_bhv++) {
            moveDirection += (*it_bhv)->calculateMoveDirection(**it_predator, obstacleList) * (*it_bhv)->weight;
            if (isnan(moveDirection.x) || isnan(moveDirection.y) || isnan(moveDirection.z)) {
                std::cout << "FOUND NAN" << std::endl;
                exit(0);
            }
        }
        // avoid obstabcle is a hard rule
        AvoidObs bhv(0, config->obsRadius, nullptr);
        vec3 direction = bhv.calculateMoveDirection(**it_predator, obstacleList);
        if (direction.magnitude() != 0) {
            moveDirection = direction * moveDirection.magnitude() * 4 ;
            //std::cout << "dir = (" << moveDirection.x << ", " << moveDirection.y << ", " << moveDirection.z << std::endl;
        }
        //std::cout << "moveDirection = (" << moveDirection.x << ", " << moveDirection.y << ", " << moveDirection.z << std::endl;     
        (*it_predator)->setMoveDirection(moveDirection);

    }
}

vec3 Simulation::getValidCreaturePos() {
    while (true) {
        vec3 randPos = getRandomCreaturePos();
        bool valid = true;
        for (auto obs : obstacleList) {
            if (obs->isContainPoint(vec2(randPos.x, randPos.y))) {
                valid = false;
                break;
            }
        }
        if (valid)
            return randPos;
    }
}

vec3 Simulation::getRandomCreaturePos() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(-min(windowSize.x, windowSize.y)+2*config->margin, min(windowSize.x, windowSize.y)-2*config->margin);

    return vec3(distr(gen), distr(gen), 0);
}

float Simulation::getRandomLife(float life) {
    std::random_device rd;
    std::mt19937 gen(rd());
    // life : 80% ~ 120% average life time
    std::uniform_int_distribution<> distr(-20, 20);
    return life * (100 + distr(gen)) / 100;
}