//
//  Entity.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-31.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include "Game.hpp"

class Entity {
    
public:
    Entity(const size_t id, const std::string& tag, const std::vector<char*> textureSheet, int x, int y);
    
    void update();
    void render();
    void animate();
    
    std::string getTag();
    bool isActive();
    
    void destroy();
    
private:
    int xPos_;
    int yPos_;
    
    size_t      id_     = 0;
    std::string tag_    = "Default";
    bool        active_ = true;
    
    SDL_Rect    srcRect_, destRect_;
    SDL_Texture *texture_;
    
    std::vector<SDL_Texture*> animTextures_;
    
};

#endif /* Entity_hpp */
