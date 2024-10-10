//
//  SSpawner.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#include "SSpawner.hpp"

/** Spawn a player! **/
std::shared_ptr<Entity> SSpawner::spawnPlayer() {
    player_ = entityManager_->addEntity("Player");
    SDL_Texture* cupid_texture = renderer_->loadTexture("cupid_idle.png");
    player_->cSprite = std::make_shared<CSprite>(cupid_texture, 128, 128);
    
    std::vector<SDL_Rect> cupid_clips;
    for (int i = 0; i < 8; i++) {
        int h = player_->cSprite->getHeight();
        int w = player_->cSprite->getWidth();
        SDL_Rect clip = { i * w, 0, w, h };
        cupid_clips.push_back(clip);
    }
    player_->cAnimator = std::make_shared<CAnimator>(8, 8, cupid_clips);
    
    Vec2 cupid_pos (336.0, 256.0);
    Vec2 cupid_velo (0.0, 0.0);
    
    player_->cTransform = std::make_shared<CTransform>(3.0, cupid_pos, cupid_velo, 0.0, SDL_FLIP_NONE);
    
    return player_;
}

/** Spawn a single NPC (enemy)! **/
std::shared_ptr<Entity> SSpawner::spawnEnemy() {
    if (player_ == nullptr) {
        printf("Error: Player not initialized yet.");
        return nullptr;
    }
    
    if (!incrementRate(counter_, spawnRate_)) {
        return nullptr;
    }
    
    std::shared_ptr<Entity> npc = entityManager_->addEntity("NPC");
    if (npc == nullptr) {
        printf("Too many entities in the game. Try again later!");
        return nullptr;
    }
     
    // Choose random angle from player to spawn from
    int range = 360 + 1;
    float npc_angle = (std::rand() % range) * M_PI / 180;
    
    Vec2 dist = Vec2(cosf(npc_angle), sinf(npc_angle)) * 600;
    Vec2 p_pos = player_->cTransform->pos;
    Vec2 npc_pos = p_pos + dist;
    
    // Set speed of npc and create transform
    Vec2 npc_velo = (p_pos - npc_pos).normalize() * NPC_SPEED;
    npc->cTransform = std::make_shared<CTransform>(NPC_SPEED, npc_pos, npc_velo, 0.0, SDL_FLIP_NONE);
     
    // Make the sprite!
    SDL_Texture* npc_tex = renderer_->loadTexture("npc_green.png");
    npc->cSprite = std::make_shared<CSprite>(npc_tex, 64, 64);
    
    // Make animation!!
    std::vector<SDL_Rect> npc_clips;
    for (int i = 0; i < 4; i++) {
        SDL_Rect clip = { i * 64, 0, 64, 64 };
        npc_clips.push_back(clip);
    }
    npc->cAnimator = std::make_shared<CAnimator>(4, 10, npc_clips);
    
    return npc;
}

/** Update transform targets so that enemies are always moving towards the player! */
void SSpawner::updateEnemy(std::shared_ptr<Entity> npc) {
    if (player_ == nullptr) {
        printf("Error: Player not initialized yet.");
        return;
    }
    
    if (npc == nullptr) {
        printf("Error: NPC doesn't exist.");
        return;
    }
    
    npc->cTransform->setTarget(player_->cTransform->pos);
}
