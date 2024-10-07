//
//  SEnemySpawner.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-05.
//

#include "SEnemySpawner.hpp"

void sSpawnEnemy(std::shared_ptr<Entity> player) {
    std::shared_ptr<Entity> npc = Game::entityManager->addEntity("NPC");
     
    // Choose random angle from player to spawn from
    int range = 360 + 1;
    float npc_angle = (std::rand() % range) * M_PI / 180;
    
    Vec2 dist = Vec2(cosf(npc_angle), sinf(npc_angle)) * 200;
    Vec2 p_pos = player->cTransform->pos;
    Vec2 npc_pos = p_pos + dist;
    printf("(%f, %f)", npc_pos.x, npc_pos.y);
    
    // Set speed of npc and create transform
    Vec2 npc_velo = (p_pos - npc_pos).normalize() * NPC_SPEED;
    npc->cTransform = std::make_shared<CTransform>(NPC_SPEED, npc_pos, npc_velo, 0.0, SDL_FLIP_NONE);
     
    // Make the sprite!
    SDL_Texture* npc_tex = TextureManager::loadTexture("npc_walk_0.png");
    npc->cSprite = std::make_shared<CSprite>(npc_tex, 64, 64);
    
    // Make animation!!
    std::vector<SDL_Rect> npc_clips;
    for (int i = 0; i < 4; i++) {
        SDL_Rect clip = { i * 64, 0, 64, 64 };
        npc_clips.push_back(clip);
    }
    npc->cAnimator = std::make_shared<CAnimator>(4, 10, npc_clips);
}

/** Update locations so that enemies are always moving towards the player! */
void sEnemyUpdate(std::shared_ptr<Entity> npc, std::shared_ptr<Entity> player) {
    npc->cTransform->setTarget(player->cTransform->pos);
}




