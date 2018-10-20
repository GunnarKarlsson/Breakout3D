#ifndef COLLISION_H
#define COLLISION_H

#include "common.h"
#include "entity.h"

bool valueInRange(int value, int min, int max) {
    return (value >= min) && (value <= max);
}

bool rectOverlap(rect A, rect B) {
    bool xOverlap = valueInRange(A.x, B.x, B.x + B.width) ||
                    valueInRange(B.x, A.x, A.x + A.width);

    bool yOverlap = valueInRange(A.y, B.y, B.y + B.height) ||
                    valueInRange(B.y, A.y, A.y + A.height);

    return xOverlap && yOverlap;
}

bool haveCollided(Entity *e1, Entity *e2) {

    rect eRect;
    eRect.x = e1->xPos;
    eRect.y = e1->yPos;
    eRect.width = 1;
    eRect.height = 1;

    rect pRect;
    pRect.x = e2->xPos;
    pRect.y = e2->yPos;
    pRect.width = 1;
    pRect.height = 1;

    return rectOverlap(eRect, pRect);
}

#endif // COLLISION_H
