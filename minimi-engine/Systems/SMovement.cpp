//
//  SMovement.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-04.
//

#include "SMovement.hpp"

/** Move an entity (for now, just NPCs) according to the target set in their Transform. **/
void moveNPC(std::shared_ptr<Entity> entityToMove) {
    if (entityToMove->cTransform && entityToMove->getTag() != "Player") {
        float speed = entityToMove->cTransform->speed;
        
        // Get the vector pointing towards the player
        Vec2 dist_vec = entityToMove->cTransform->getTarget() - entityToMove->cTransform->pos;
        dist_vec.normalize();
        
        // Flip the NPC if needed
        if (dist_vec.x < 0) {
            entityToMove->cTransform->flip = SDL_FLIP_HORIZONTAL;
        } else {
            entityToMove->cTransform->flip = SDL_FLIP_NONE;
        }
        
        Vec2 old_pos = entityToMove->cTransform->pos; // Shallow copy for collider
        
        // Move the NPC towards the player
        entityToMove->cTransform->velocity = dist_vec * speed;
        entityToMove->cTransform->pos.add(entityToMove->cTransform->velocity);
         
        // Move the NPC's collider
        // This ensures that an offsetted collider will still follow the entity correctly
        int x = static_cast<int>(entityToMove->cTransform->pos.x) - static_cast<int>(old_pos.x);
        int y = static_cast<int>(entityToMove->cTransform->pos.y) - static_cast<int>(old_pos.y);

        entityToMove->cBoxCollider->collider.x += x;
        entityToMove->cBoxCollider->collider.y += y;
    }
}

/** Move the player based on user inputs. **/
void movePlayer(std::shared_ptr<Entity> player, MovementInputs *inputs) {
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
        
        Vec2 old_pos = player->cTransform->pos; // make a shallow copy of the old position
        
        player->cTransform->pos.add(player->cTransform->velocity);
        
        // This ensures that an offsetted collider will still follow the player correctly
        int x = static_cast<int>(player->cTransform->pos.x) - static_cast<int>(old_pos.x);
        int y = static_cast<int>(player->cTransform->pos.y) - static_cast<int>(old_pos.y);
    
        player->cBoxCollider->collider.x += x;
        player->cBoxCollider->collider.y += y;
    }
}

/** Rotate the bow around the player in a circle. */
void moveBow(std::shared_ptr<Entity> bow, std::shared_ptr<Entity> player) {
    Vec2 p_pos = player->cTransform->pos;
    
    int p_width = player->cSprite->getWidth();
    
    bow->cTransform->pos = p_pos - Vec2(p_width / 2 - 10, 0);
    bow->cTransform->degrees = static_cast<double>((static_cast<int>(bow->cTransform->degrees) - 2) % 360);
}

void moveArrow(std::shared_ptr<Entity> arrow, std::shared_ptr<Entity> bow, std::shared_ptr<Entity> player) {
    if (arrow->cTransform->velocity.x != 0.0 && arrow->cTransform->velocity.y != 0.0) {
        Vec2 old_pos = arrow->cTransform->pos; // make a shallow copy of the old position

        arrow->cTransform->pos.add(arrow->cTransform->velocity);
        // ------ Move collider! ------
        // This ensures that an offsetted collider will still follow the player correctly
        int x = static_cast<int>(arrow->cTransform->pos.x) - static_cast<int>(old_pos.x);
        int y = static_cast<int>(arrow->cTransform->pos.y) - static_cast<int>(old_pos.y);
    
        arrow->cBoxCollider->collider.x += x;
        arrow->cBoxCollider->collider.y += y;
    } else {
        // Continue rotating around player
        Vec2 p_pos = player->cTransform->pos;
        int p_width = player->cSprite->getWidth();
        
        arrow->cTransform->pos = p_pos - Vec2(p_width / 2 + 10, 0);
        arrow->cTransform->degrees = bow->cTransform->degrees;
    }
}
