//
//  TextureManager.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-23.
//
#pragma once
#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <stdio.h>
#include "Game.hpp"

class TextureManager {
public:
    static SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* renderer);
};

#endif /* TextureManager_hpp */
