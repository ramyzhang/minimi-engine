//
//  SSpawner.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#include "SSpawner.hpp"

void SSpawner::init(Observer *ob) {
    spawnPlayer();
    addObserver(ob);
}

void SSpawner::update(MouseInputs inputs_) {
    if (inputs_.mouse == MOUSE_DOWN) {
        std::shared_ptr<Entity> new_arrow = spawnArrow();
        notify(ARROW_SHOT);
    }
    
    spawnEnemy();
    
    for (auto& e : entityManager_->getEntities("NPC")) {
        if (e->cTransform) updateEnemy(e);
    }
}

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
    
    player_->cTransform = std::make_shared<CTransform>(CUPID_SPEED, cupid_pos, cupid_velo, 0.0, SDL_FLIP_NONE);
    
    int x = static_cast<int>(cupid_pos.x);
    int y = static_cast<int>(cupid_pos.y);
    SDL_Rect cupid_collider = { x + 32, y + 36, player_->cSprite->getWidth() / 2, player_->cSprite->getHeight() / 2 };
    
    player_->cBoxCollider = std::make_shared<CBoxCollider>(cupid_collider);
    
    // Spawn cupid's bow
    spawnBow();
    
    return player_;
}

void SSpawner::spawnBow() {
    bow_ = entityManager_->addEntity("Bow");
    SDL_Texture* bow_texture = renderer_->loadTexture("cupid_bow.png");
    bow_->cSprite = std::make_shared<CSprite>(bow_texture, 128, 128);
    
    std::vector<SDL_Rect> bow_clips;
    for (int i = 0; i < 8; i++) {
        int h = bow_->cSprite->getHeight();
        int w = bow_->cSprite->getWidth();
        SDL_Rect clip = { i * w, 0, w, h };
        bow_clips.push_back(clip);
    }
    bow_->cAnimator = std::make_shared<CAnimator>(8, 8, bow_clips);
    
    Vec2 bow_pos (player_->cTransform->pos.x + 50, player_->cTransform->pos.y);
    Vec2 bow_velo (0.0, 0.0);
    
    int p_width = player_->cSprite->getWidth();
    int p_height = player_->cSprite->getHeight();
    
    bow_->cTransform = std::make_shared<CTransform>(player_->cTransform->speed, bow_pos, bow_velo, 0.0, SDL_FLIP_NONE);
    SDL_Point center = { p_width - 10, p_height / 2 };
    bow_->cTransform->center = center;
    
    // TODO: delete this once animation system is up
    spawnArrow(true);
}

std::shared_ptr<Entity> SSpawner::spawnArrow(bool isInit) {
    // Make the first arrow
    std::shared_ptr<Entity> arrow = entityManager_->addEntity("Arrow");
    
    // Make the sprite component
    SDL_Texture* arrow_texture = renderer_->loadTexture("cupid_arrow.png");
    arrow->cSprite = std::make_shared<CSprite>(arrow_texture, 128, 128);
     
    // Make the transform component
    int p_width = player_->cSprite->getWidth();
    int p_height = player_->cSprite->getHeight();
    
    Vec2 arrow_pos = bow_->cTransform->pos;
    Vec2 arrow_velo (0.0, 0.0);
    float speed = ARROW_SPEED;
    
    if (!isInit) {
        Vec2 p_pos = player_->cTransform->pos;
        // Convert rotation degrees to radians
        double offset = 5; // Arrow angle offset for game feel
        float angle = static_cast<float>(bow_->cTransform->degrees - offset) * M_PI / 180;
        
        arrow_pos = p_pos - Vec2(p_width / 2 + 10, 0);
        arrow_velo = Vec2(- cos(angle) * speed, - sin(angle) * speed);
        
        // ------ Init collider! ------
        Vec2 p_center = { p_pos.x + p_width / 2, p_pos.y + p_width / 2 }; // Get the center of the AABB
        Vec2 new_pos = p_center + Vec2(cosf(angle - M_PI) * 74, sinf(angle - M_PI) * 74);
        new_pos.subtract(Vec2(8, 8)); // re-center according to collision center
        
        int x = static_cast<int>(new_pos.x);
        int y = static_cast<int>(new_pos.y);
        SDL_Rect arrow_collider = { x, y, player_->cSprite->getWidth() / 8, player_->cSprite->getHeight() / 8 };
        
        arrow->cBoxCollider = std::make_shared<CBoxCollider>(arrow_collider);
        arrow->cTransform = std::make_shared<CTransform>(speed, arrow_pos, arrow_velo, bow_->cTransform->degrees - offset, SDL_FLIP_NONE);
        
        arrow->cPhysics = std::make_shared<CPhysics>(ARROW_FRICTION);
    } else {
        arrow->cTransform = std::make_shared<CTransform>(speed, arrow_pos, arrow_velo, bow_->cTransform->degrees, SDL_FLIP_NONE);
    }
    
    SDL_Point center = { p_width + 10, p_height / 2 };
    arrow->cTransform->center = center;
    
    return arrow;
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
    
    Vec2 dist = Vec2(cosf(npc_angle * 180 / M_PI), sinf(npc_angle * 180 / M_PI)) * 600;
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
    
    int x = static_cast<int>(npc_pos.x);
    int y = static_cast<int>(npc_pos.y);
    SDL_Rect npc_collider = { x + 16, y + 5, npc->cSprite->getWidth() / 2, npc->cSprite->getHeight() - 12 };
    
    npc->cBoxCollider = std::make_shared<CBoxCollider>(npc_collider);
    
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
