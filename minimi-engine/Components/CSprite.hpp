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
#include <vector>
#include "Component.hpp"

class CSprite : public Component {
public:
    SDL_Texture* texture;
    
    int getWidth() { return width_; };
    int getHeight() { return height_; };
    
    int alpha;
    
    CSprite() {};
    CSprite(SDL_Texture* tex,
            const int& w,
            const int& h) : texture(tex), width_(w), height_(h) {};

private:
    int width_;
    int height_;    
};

#endif /* CSprite_hpp */
