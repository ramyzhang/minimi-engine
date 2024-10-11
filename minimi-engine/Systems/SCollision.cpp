//
//  SCollision.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#include "SCollision.hpp"

bool checkCollision(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    SDL_Rect rect_a = a->cBoxCollider->collider;
    SDL_Rect rect_b = b->cBoxCollider->collider;
    
    // check x axis collision
    if (rect_a.x + rect_a.w <= rect_b.x) {
        return false;
    }
    
    if (rect_a.x >= rect_b.x + rect_b.w) {
        return false;
    }
    
    // check y axis collision
    if (rect_a.y + rect_a.h <= rect_b.y) {
        return false;
    }
    
    if (rect_a.y >= rect_b.y + rect_b.h ) {
        return false;
    }
    
    return true;
}
