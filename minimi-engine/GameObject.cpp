//
//  GameObject.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-23.
//

#include "GameObject.hpp"

GameObject::GameObject(const std::vector<char*> textureFiles, int x, int y) {
    xPos_ = x;
    yPos_ = y;
    for (char* fileName : textureFiles) {
        animTextures_.push_back(TextureManager::loadTexture(fileName));
    }
    texture_ = TextureManager::loadTexture(textureFiles[0]);
}

void GameObject::update() {
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

void GameObject::render() {
    SDL_RenderCopy(Game::renderer_, texture_, &srcRect_, &destRect_);
}

void GameObject::animate() {
    int currFrame = ((xPos_ / 8) % animTextures_.size());
    texture_ = animTextures_[currFrame];
}
