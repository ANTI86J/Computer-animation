#include "creature.h"

Creature::Creature() {
    this->position = vec3(0, 0, 0);
    this->moveDirection = vec3(0, 0, 0);
    this->moveSpeed = 0;
    this->life = 0;
    this->color = vec4();
    this->size = 0.0;
    this->dead = false;
}

Creature::Creature(vec3 position, vec3 moveDirection, float moveSpeed, float life, float size, vec4 color) {
    this->position = position;
    this->moveDirection = moveDirection;
    this->moveSpeed = moveSpeed;
    this->life = life;

    this->size = size;
    this->color = color;

    this->dead = false;
}

vec3 Creature::getPosition() { return position; }
vec3 Creature::getMoveDirection() { return moveDirection; }
void Creature::setMoveDirection(const vec3& dir) { moveDirection = dir; }

bool Creature::isDead() { return dead; }
void Creature::setDead(bool v) { dead = v; }

void Creature::update(float dt) {
    if (dead) return;
    fade(dt);
    move(dt);
    //printStats();
}

void Creature::draw() {
    if (dead) return;
    glColor3f(color.x, color.y, color.z);
    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(position.x, position.y, position.z);

    glutSolidCube(size);

    glPopMatrix();
}

void Creature::fade(float dt) {
    if (life <= 0) 
        dead = true;
    else 
        life -= dt;
}
void Creature::move(float dt) {
    position += moveDirection.normalize() * moveSpeed * dt;
    //printStats();
}

void Creature::printStats() {
    debugLog(moveDirection.normalize(), "MOVING WITH DIR: ");
}


void Predator::prey(Creature& creature)
{
    creature.setDead(true);
}