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
#include "Vec2.hpp"
#include "CSprite.hpp"

class TextureManager {
    
public:
    static SDL_Texture* loadTexture(const char* fileName);
    static void draw(std::shared_ptr<CSprite> sprite, Vec2 position, SDL_Rect* clip = NULL);
    static void drawTile(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect);
    static void free(std::shared_ptr<CSprite> sprite);
};

#endif /* TextureManager_hpp */
