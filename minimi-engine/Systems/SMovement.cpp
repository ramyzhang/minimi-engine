//
//  SMovement.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-04.
//

#include "SMovement.hpp"

void moveEntity(std::shared_ptr<Entity> entityToMove) {
    if (entityToMove->cTransform && entityToMove->getTag() != "Player") {
        float speed = entityToMove->cTransform->speed;
        Vec2 dist_vec = entityToMove->cTransform->getTarget() - entityToMove->cTransform->pos;
        dist_vec.normalize();
        
        if (dist_vec.x < 0) {
            entityToMove->cTransform->flip = SDL_FLIP_HORIZONTAL;
        } else {
            entityToMove->cTransform->flip = SDL_FLIP_NONE;
        }
        
        entityToMove->cTransform->velocity = dist_vec * speed;
        entityToMove->cTransform->pos.add(entityToMove->cTransform->velocity);
    }
}

void movePlayer(std::shared_ptr<Entity> player) {
    if (player->cTransform) {
        float speed = player->cTransform->speed;
        
        switch (Game::getInputs()->up) {
            case GO: player->cTransform->velocity.add(Vec2(0, -speed)); break;
            case STOP: player->cTransform->velocity.add(Vec2(0, speed)); break;
            default: break;
        }
        
        Game::getInputs()->up = NEUTRAL;
        
        switch (Game::getInputs()->down) {
            case GO: player->cTransform->velocity.add(Vec2(0, speed)); break;
            case STOP: player->cTransform->velocity.add(Vec2(0, -speed)); break;
            default: break;
        }
        
        Game::getInputs()->down = NEUTRAL;

        switch (Game::getInputs()->left) {
            case GO:
                player->cTransform->velocity.add(Vec2(-speed, 0));
                if (player->cTransform->degrees > -10.0) {
                    player->cTransform->degrees = -10.0;
                }
                player->cTransform->flip = SDL_FLIP_HORIZONTAL;
                break;
            case STOP:
                player->cTransform->velocity.add(Vec2(speed, 0));
                if (player->cTransform->degrees < 0.0) {
                    player->cTransform->degrees = 0.0;
                }
                break;
            default: break;
        }
        
        Game::getInputs()->left = NEUTRAL;

        switch (Game::getInputs()->right) {
            case GO:
                player->cTransform->velocity.add(Vec2(speed, 0));
                if (player->cTransform->degrees < 10.0) {
                    player->cTransform->degrees = 10.0;
                }
                player->cTransform->flip = SDL_FLIP_NONE;
                break;
            case STOP:
                player->cTransform->velocity.add(Vec2(-speed, 0));
                if (player->cTransform->degrees > 0.0) {
                    player->cTransform->degrees = 0.0;
                }
                break;
            default: break;
        }
        
        Game::getInputs()->right = NEUTRAL;
        
        player->cTransform->pos.add(player->cTransform->velocity);
    }
}
