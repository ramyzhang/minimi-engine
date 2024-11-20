//
//  SCollision.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#include "SCollision.hpp"

void SCollision::init(std::shared_ptr<Entity> player, Observer *obs) {
    player_ = player;
    addObserver(obs);
}

void SCollision::update() {
    for (auto& e : em_->getEntities("NPC")) {
        if (e->cBoxCollider) {
            if (checkCollision(e, player_)) {
                e->destroy();
                notify(PLAYER_HIT);
            }
            
            for (auto& arrow : em_->getEntities("Arrow")) {
                if (arrow->cBoxCollider && checkCollision(arrow, e)) {
                    e->destroy();
                    arrow->destroy();
                    notify(ENEMY_DIED);
                }
            }
        }
    }
}

/** AABB Collision solver. */
bool SCollision::checkCollision(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
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
