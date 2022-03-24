#include "Vec2.h"

Vec2_t AddVec(Vec2_t a, Vec2_t b){
    Vec2_t c = {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
    return c;
}