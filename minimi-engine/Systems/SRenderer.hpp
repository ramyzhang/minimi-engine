//
//  SRenderer.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#ifndef SRenderer_hpp
#define SRenderer_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Vec2.hpp"
#include "Entity.hpp"
#include "CSprite.hpp"

void sRenderEntity(std::shared_ptr<Entity> e);
class SRenderer {
public:
    SRenderer() {};
    ~SRenderer() {};
    
    SRenderer(SDL_Renderer* r) : renderer_(r) {};
    
    SDL_Texture* loadTexture(const char* fileName);
    
    void draw(std::shared_ptr<Entity> e);
    
    // overloaded draw function for non-gameobject tiles
    void draw(SDL_Texture* texture,
              SDL_Rect* srcRect,
              SDL_Rect* destRect);
    
    void free(std::shared_ptr<CSprite> sprite);

private:
    SDL_Renderer* renderer_;
};

#endif /* SRenderer_hpp */
