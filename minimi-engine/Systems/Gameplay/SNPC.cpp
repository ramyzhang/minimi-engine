//
//  SNPC.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-12-05.
//

#include "SNPC.hpp"

void SNPC::init(std::shared_ptr<Entity> player) {
    player_ = player;
}

void SNPC::update() {
    for (auto& e : em_->getEntities("NPC")) {
        if (e->cTransform) updateTargetPosition(e);
    }
}

void SNPC::updateTargetPosition(std::shared_ptr<Entity> npc) {
    if (!npc->cNPC) return;
    
    switch (npc->cNPC->state) {
        case ATTACKING:
            if (player_) {
                npc->cNPC->setTarget(player_->cTransform->pos);
            }
            break;
        case FADING:
            npc->cSprite->alpha = (npc->cSprite->alpha - 5) % 255;
            if (npc->cSprite->alpha < 10) {
                npc->destroy();
            }
        default:
            break;
    }
}

void SNPC::findLoveTarget(std::shared_ptr<Entity> npc) {
    if (!npc->cNPC) return;
    
    npc->cBoxCollider.reset(); // we no longer want it to be able to collide   
    npc->cNPC->state = FADING;
    npc->cSprite->alpha = (npc->cSprite->alpha - 5) % 255;
    
//    em_->changeTag("LoveNPC", npc); // change the tag of the npc;
//    
//    if (em_->getEntities("LoveNPC").size() > 0) {
//        // don't move!
//    }
}

