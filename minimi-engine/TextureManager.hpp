//
//  TextureManager.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-23.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <stdio.h>
#include "Game.hpp"

class TextureManager {
    
public:
    static SDL_Texture* loadTexture(const char* fileName);
    static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
};

#endif /* TextureManager_hpp */
