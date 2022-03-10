#include "behavior.h"

Behavior::Behavior(float weight, std::vector<Creature*>* context) {
    this->weight = weight;
    this->context = context;
}

Separation::Separation(float weight, float radius, std::vector<Creature*>* context) : Behavior(weight, context) {
    this->radius = radius;
    
}

vec3 Separation::calculateMoveDirection(Creature& boid, const std::vector<Obstacle*>& obs) {
    vec3 result = vec3();
    vec3 boidPos = boid.getPosition();
    int count = 0;

    for (auto it = context->begin(); it != context->end(); it++) {
        if (*it == &boid) continue;
        if ((*it)->isDead()) continue;

        vec3 contextPos = (*it)->getPosition();

        if (contextPos.sqrDist(boidPos) <= pow(radius, 2)) {
            result += boidPos - contextPos;
            count++;
        }
    }
    if (count > 0) {
        result /= count;
    }
    return result.normalize();
}

Cohesion::Cohesion(float weight, float radius, std::vector<Creature*>* context) : Behavior(weight, context) {
    this->radius = radius;
}

vec3 Cohesion::calculateMoveDirection(Creature& boid, const std::vector<Obstacle*>& obs) {
    vec3 result = vec3();
    vec3 boidPos = boid.getPosition();
    int count = 0;

    for (auto it = context->begin(); it != context->end(); it++) {
        if ((*it)->isDead()) continue;
        vec3 contextPos = (*it)->getPosition();

        if (contextPos.sqrDist(boidPos) <= pow(radius, 2)) {
            result += contextPos;
            count++;
        }

    }
    if (count > 0) {
        result /= count;
    }

    result = (result - boidPos);
    // Maybe change this smoothing later
    result = vec3Lerp(boid.getMoveDirection(), result, 0.1);
    return result.normalize();
}

Alignment::Alignment(float weight, float radius, std::vector<Creature*>* context) : Behavior(weight, context) {
    this->radius = radius;
}

vec3 Alignment::calculateMoveDirection(Creature& boid, const std::vector<Obstacle*>& obs) {
    vec3 result = vec3();
    vec3 boidPos = boid.getPosition();
    int count = 0;

    for (auto it = context->begin(); it != context->end(); it++) {
        if ((*it)->isDead()) continue;
        vec3 contextPos = (*it)->getPosition();

        if (contextPos.sqrDist(boidPos) <= pow(radius, 2)) {
            result += (*it)->getMoveDirection();
            count++;
        }
    }
    if (count > 0) {
        result /= count;
    }
    return result.normalize();
}

AvoidObs::AvoidObs(float weight, float radius, std::vector<Creature*>* context) : Behavior(weight, context) {
    this->radius = radius;
}

vec3 AvoidObs::calculateMoveDirection(Creature& boid, const std::vector<Obstacle*>& obs) {
    vec3 result = vec3();
    vec3 boidPos = boid.getPosition();
    vec3 boidDir = boid.getMoveDirection().normalize();

    int count = 0;

    vec2 start = vec2(boidPos.x, boidPos.y);
    vec2 end = vec2(boidPos.x + radius * boidDir.x, boidPos.y + radius * boidDir.y);

    for (auto o : obs) {
        //vec4 bltr = o->getPosition();
        /*
               --------
               |      |
               |      |
               |------|
        */
        vec2 intersect_point = vec2(0, 0);
        float distance = 10e6;
        bool cross = false;
        LinePos lp = NONE;
        //if (updateIntersectDist(start, end, o->getBottomLeft(), o->getBottomRight(), &distance, &intersect_point)) {
        if (intersect(start, radius, o->getBottomLeft(), o->getBottomRight())) {
            lp = BOTTOM;
            cross = true;
        }
        //if (updateIntersectDist(start, end, o->getBottomLeft(), o->getTopLeft(), &distance, &intersect_point)) {
        if (intersect(start, radius, o->getBottomLeft(), o->getTopLeft())) {
            lp = LEFT;
            cross = true;
        }
        //if (updateIntersectDist(start, end, o->getTopLeft(), o->getTopRight(), &distance, &intersect_point)) {
        if (intersect(start, radius, o->getTopLeft(), o->getTopRight())) {
            lp = TOP;
            cross = true;
        }
        //if (updateIntersectDist(start, end, o->getTopRight(), o->getBottomRight(), &distance, &intersect_point)) {
        if (intersect(start, radius, o->getTopRight(), o->getBottomRight())) {
            lp = RIGHT;
            cross = true;
        }
        
        if (cross) {
            float ratio = 0; 
            //if (start.dist(end) != 0)
            //    ratio = intersect_point.dist(end) / start.dist(end);
            // result += (*it)->getMoveDirection();
            switch (lp) {
            case LEFT:
               /*
               if (boidDir.y > 0) {  // Up
                   result += vec3(0, 1, 0) * (1-ratio) + vec3(-1, 0, 0) * ratio;
               }
               else { // Down
                   result += vec3(0, -1, 0) * (1 - ratio) + vec3(-1, 0, 0) * ratio;
               }
               */
                //result += vec3(-boidDir.x, boidDir.y, 0);
                result += vec3(-1, 0, 0);
                break;
            case RIGHT:
                /*
                if (boidDir.y > 0) { // Up
                    result += vec3(0, 1, 0) * (1 - ratio) + vec3(1, 0, 0) * ratio;
                }
                else { // Down
                    result += vec3(0, -1, 0) * (1 - ratio) + vec3(1, 0, 0) * ratio;
                }
                */
                //result += vec3(-boidDir.x, boidDir.y, 0);
                result += vec3(1, 0, 0);
                break;
            case TOP:
                /*
                if (boidDir.x > 0) { // Right
                    result += vec3(1, 0, 0) * (1 - ratio) + vec3(0, 1, 0) * ratio;
                }
                else {   // Left
                    result += vec3(-1, 0, 0) * (1 - ratio) + vec3(0, 1, 0) * ratio;
                }
                */
                //result += vec3(boidDir.x, -boidDir.y, 0);
                result += vec3(0, 1, 0);
                break;
            case BOTTOM:
                /*
                if (boidDir.x > 0) { // Right
                    result += vec3(1, 0, 0) * (1 - ratio) + vec3(0, -1, 0) * ratio;
                }
                else {   // Left
                    result += vec3(-1, 0, 0) * (1 - ratio) + vec3(0, -1, 0) * ratio;
                }
                */
                //result += vec3(boidDir.x, -boidDir.y, 0);
                result += vec3(0, -1, 0);
                break;
            default:
                break;
            }
            count++;
            //return result.normalize();
        }

    }

    if (count > 0) {
        result /= count;
        //std::cout << "omgomg count = " << count << ", result = (" << result.x << ", " << result.y << ")" << std::endl;
    }

    return result.normalize();
}

bool AvoidObs::updateIntersectDist(const vec2& start, const vec2& end, const vec2& ls, const vec2& le, float* distance, vec2* intersect_point)
{
    vec2 ip = vec2(0, 0);
    if (intersect(start, end, ls, le, &ip)) {
        float cur_dist = ip.dist(start);
        if (cur_dist < *distance) {
            intersect_point->x = ip.x;
            intersect_point->y = ip.y;
            *distance = cur_dist;
            return true;
        } 
    }
    return false;
}


Prey::Prey(float weight, float radius, std::vector<Creature*>* context) : Behavior(weight, context) {
    this->radius = radius;
}

vec3 Prey::calculateMoveDirection(Creature& boid, const std::vector<Obstacle*>& obs) {
    vec3 result = vec3();
    vec3 boidPos = boid.getPosition();

    for (auto it = context->begin(); it != context->end(); it++) {
        if ((*it)->isDead()) continue;
        vec3 contextPos = (*it)->getPosition();

        if (contextPos.sqrDist(boidPos) <= pow(radius, 2)) {
            (*it)->setDead(true);
            break; // prey single creature once
        }
    }

    return result;
}