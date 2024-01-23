//
//  GameObject.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-23.
//

#include "GameObject.hpp"

GameObject::GameObject(const char* textureFile, SDL_Renderer* renderer, int x, int y) {
    xPos_ = x;
    yPos_ = y;
    renderer_ = renderer;
    texture_ = TextureManager::loadTexture(textureFile, renderer_);
}

void GameObject::update() {
//    xPos_ = ((xPos_ + 1) % 1056) - 256;
//    yPos_ = sin((yPos_ + 1) * 0.15) * 10;
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
}

void GameObject::render() {
    SDL_RenderCopy(renderer_, texture_, &srcRect_, &destRect_);
}
