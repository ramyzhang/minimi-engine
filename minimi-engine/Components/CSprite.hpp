//
//  CSprite.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-09-20.
//

#ifndef CSprite_hpp
#define CSprite_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Component.hpp"

class CSprite : public Component {
public:
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    CSprite() {};
    CSprite(SDL_Texture* tex, const SDL_Rect& src, const SDL_Rect& dest) : texture(tex), srcRect(src), destRect(dest) {};
};

#endif /* CSprite_hpp */
