//
//  SAnimation.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-19.
//

#include "SAnimation.hpp"

void SAnimation::npcStateMachine(Event event, std::shared_ptr<Entity> entity) {
    printf("NPC state machine notified!");
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
            printf("At 0 for bow\n");
            if (event == ARROW_SHOT) {
                bow->cAnimator->setLooping(false);
                bow->cAnimator->setSpriteClip(1);
            }
        case 1: // shooting bow - just ignore, it'll go back to idling
            printf("At 1 for bow\n");
            break;
    }
};
