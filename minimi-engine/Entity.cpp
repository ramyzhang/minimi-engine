//
//  Entity.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-31.
//

#include "Entity.hpp"

Entity::Entity(const size_t id, const std::string& tag, const std::vector<char*> textureSheet, int x, int y) {
    id_ = id;
    tag_ = tag;
    xPos_ = x;
    yPos_ = y;
    
    for (char* fileName : textureSheet) {
        animTextures_.push_back(TextureManager::loadTexture(fileName));
    }
    
    texture_ = TextureManager::loadTexture(textureSheet[0]);
}

void Entity::update() {
    xPos_++;
    yPos_++;
    
    srcRect_.h = 64;
    srcRect_.w = 64;
    srcRect_.x = 0;
    srcRect_.y = 0;
    
    destRect_.h = srcRect_.h * 2;
    destRect_.w = srcRect_.w * 2;
    destRect_.x = (xPos_ % 1056) - 64;
    destRect_.y = sin(yPos_ * 0.15) * 10;
    
    this->animate();
}

void Entity::render() {
    SDL_RenderCopy(Game::renderer_, texture_, &srcRect_, &destRect_);
}

void Entity::animate() {
    int currFrame = ((xPos_ / 8) % animTextures_.size());
    texture_ = animTextures_[currFrame];
}

std::string Entity::getTag() {
    return tag_;
}

bool Entity::isActive() {
    return active_;
}

void Entity::destroy() {
    active_ = false;
}
