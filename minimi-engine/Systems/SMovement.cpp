//
//  SMovement.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-04.
//

#include "SMovement.hpp"

/** Move an entity (for now, just NPCs) according to the target set in their Transform. **/
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

/** Move the player based on user inputs. **/
void movePlayer(std::shared_ptr<Entity> player, Inputs *inputs) {
    if (player->cTransform) {
        float speed = player->cTransform->speed;
        
        switch (inputs->up) {
            case GO: player->cTransform->velocity.add(Vec2(0, -speed)); break;
            case STOP: player->cTransform->velocity.add(Vec2(0, speed)); break;
            default: break;
        }
        
        inputs->up = NEUTRAL;
        
        switch (inputs->down) {
            case GO: player->cTransform->velocity.add(Vec2(0, speed)); break;
            case STOP: player->cTransform->velocity.add(Vec2(0, -speed)); break;
            default: break;
        }
        
        inputs->down = NEUTRAL;

        switch (inputs->left) {
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
        
        inputs->left = NEUTRAL;

        switch (inputs->right) {
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
        
        inputs->right = NEUTRAL;
        
        player->cTransform->pos.add(player->cTransform->velocity);
    }
}
