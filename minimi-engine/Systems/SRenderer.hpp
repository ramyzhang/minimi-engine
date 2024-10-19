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

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

class SRenderer {
public:
    SRenderer() {};
    ~SRenderer() {};
        
    SDL_Texture* loadTexture(const char* fileName);
    
    bool init();
    
    void draw(std::shared_ptr<Entity> e);
    
    // overloaded draw function for non-gameobject tiles
    void draw(SDL_Texture* texture,
              SDL_Rect* srcRect,
              SDL_Rect* destRect);
    
    void free(std::shared_ptr<CSprite> sprite);
    void clean();
    
    SDL_Renderer* getRenderer() { return renderer_; };

private:
    SDL_Renderer* renderer_;
    SDL_Window* window_;
};

#endif /* SRenderer_hpp */
