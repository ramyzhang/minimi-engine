//
//  GameObject.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-23.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "Game.hpp"

class GameObject {
    
public:
    GameObject(const std::vector<char*> textureSheet, int x, int y);
    ~GameObject();
    
    void update();
    void render();
    void animate();
    
private:
    int xPos_;
    int yPos_;
    
    SDL_Rect srcRect_, destRect_;
    SDL_Texture *texture_;
    
    std::vector<SDL_Texture*> animTextures_;
};

#endif /* GameObject_hpp */
