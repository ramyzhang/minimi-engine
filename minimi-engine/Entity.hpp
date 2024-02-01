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

class Component;

class Entity {
    
public:
    friend class EntityManager; // only allow EntityManager to access private variables
    
    void update();
    void render();
    void animate(); // TODO: delete after component is implemented
    
    std::string getTag();
    bool isActive();
    
    void destroy();
    
    template <typename T>
    void addComponent(T component); // add a new component of the desired type
    template <typename T>
    T& getComponent(); // return a reference of the desired component type
    
private:
    // Constructor is private; only EntityManager can make new Entities
    // TODO: params should be changed once ECS is implemented
    Entity(const size_t id, const std::string& tag, const std::vector<char*> textureSheet, int x, int y);
    
    std::vector<Component> components_;
    
    size_t      id_     = 0;
    std::string tag_    = "Default";
    bool        active_ = true;
    
    // TODO: all this below should be gone by the time ECS is finished implementation
    int xPos_;
    int yPos_;
    
    SDL_Rect    srcRect_, destRect_;
    SDL_Texture *texture_;
    
    std::vector<SDL_Texture*> animTextures_;
    
};

#endif /* Entity_hpp */
