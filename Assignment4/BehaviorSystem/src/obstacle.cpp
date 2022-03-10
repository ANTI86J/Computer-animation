#include "obstacle.h"

Obstacle::Obstacle() {
    this->bltr = vec4(0, 0, 0, 0);
    this->color = vec4();
}

Obstacle::Obstacle(vec4 bltr) {
    this->bltr = bltr;
    this->color = vec4(1,0,0,1);
}

vec4 Obstacle::getPosition() { return bltr; }

vec2 Obstacle::getBottomLeft() { return vec2(bltr.x, bltr.y); }

vec2 Obstacle::getTopLeft() { return vec2(bltr.x, bltr.w); }

vec2 Obstacle::getTopRight() { return vec2(bltr.z, bltr.w); }

vec2 Obstacle::getBottomRight() { return vec2(bltr.z, bltr.y); }


bool Obstacle::isContainPoint(vec2& p) {
    vec2 v1 = this->getTopLeft() - this->getBottomLeft();
    vec2 v2 = this->getBottomRight() - this->getBottomLeft();
    vec2 v3 = this->getBottomRight() - this->getTopRight();
    vec2 v4 = this->getTopLeft() - this->getTopRight();
    vec2 vp1 = p - this->getBottomLeft();
    vec2 vp2 = p - this->getTopRight();
    if (v1.dotProduct(vp1) > 0 && v2.dotProduct(vp1) > 0 && v3.dotProduct(vp2) > 0 && v4.dotProduct(vp2) > 0) {
        return true;
    }
    else {
        return false;
    }
}

void Obstacle::draw() {
    glColor3f(color.x, color.y, color.z);
    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(bltr.x, bltr.y,  0);
    // Currently, boid is solid cube;
    // glutSolidCube(10);
    glBegin(GL_QUADS);
    //glNormal3d(0.0, 1.0, 0.0);
    //glColor3f(1.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0);
    glVertex3d(0.0, bltr.w-bltr.y, 0);
    glVertex3d(bltr.z-bltr.x, bltr.w-bltr.y, 0);
    glVertex3d(bltr.z-bltr.x, 0.0, 0);
    glEnd();

    glPopMatrix();
}

