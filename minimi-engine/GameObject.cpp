//
//  GameObject.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-23.
//

#include "GameObject.hpp"

GameObject::GameObject(const std::vector<char*> textureFiles, SDL_Renderer* renderer, int x, int y) {
    xPos_ = x;
    yPos_ = y;
    renderer_ = renderer;
    for (char* fileName : textureFiles) {
        animTextures_.push_back(TextureManager::loadTexture(fileName, renderer_));
    }
    texture_ = TextureManager::loadTexture(textureFiles[0], renderer_);
}

void GameObject::update() {
    xPos_++;
    yPos_++;
    
    srcRect_.h = 64;
    srcRect_.w = 64;
    srcRect_.x = 0;
    srcRect_.y = 0;
    
    destRect_.h = srcRect_.h * 4;
    destRect_.w = srcRect_.w * 4;
    destRect_.x = (xPos_ % 1056) - 256;
    destRect_.y = sin(yPos_ * 0.15) * 10;
    
    this->animate();
}

void GameObject::render() {
    SDL_RenderCopy(renderer_, texture_, &srcRect_, &destRect_);
}

void GameObject::animate() {
    int currFrame = ((xPos_ / 8) % animTextures_.size());
    texture_ = animTextures_[currFrame];
}
