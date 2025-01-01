//
//  SAnimation.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-19.
//

#include "SAnimation.hpp"

void SAnimation::update() {
    std::shared_ptr<Entity> player;
    if (em_->getEntities("Player").size() > 0) {
        player = em_->getEntities("Player")[0];
    }
    
    std::shared_ptr<Entity> bow;
    if (em_->getEntities("Bow").size() > 0) {
        bow = em_->getEntities("Bow")[0];
    }
    
    if (player && player->cAnimator) player->cAnimator->incrementFrame(); // Animate player
    for (auto& e : em_->getEntities("NPC")) {
        if (e->cAnimator) e->cAnimator->incrementFrame();
    }
    if (bow && bow->cAnimator) bow->cAnimator->incrementFrame();
}

void SAnimation::npcStateMachine(Event event, std::shared_ptr<Entity> entity) {
    if (!entity->cAnimator) return;
    
    switch (entity->cAnimator->getClipIndex()) {
        case 0: // green npc :)
            if (event == ENEMY_DIED) {
                entity->cAnimator->setSpriteClip(1);
            }
        case 1: // pink npc! they will just be destroyed here, so ignore
            break;
        default:
            break;
    }
};

void SAnimation::bowStateMachine(Event event) {
    std::shared_ptr<Entity> bow = em_->getEntities("Bow")[0]; // since there can only be one bow
    
    if (!bow->cAnimator) return;
    
    switch (bow->cAnimator->getClipIndex()) {
        case 0: // idle bow
            if (event == ARROW_SHOT) {
                bow->cAnimator->setLooping(false);
                bow->cAnimator->setSpriteClip(1);
            }
        case 1: // shooting bow - just ignore, it'll go back to idling
            break;
    }
};
