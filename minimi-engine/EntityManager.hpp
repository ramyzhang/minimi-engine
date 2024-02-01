//
//  EntityManager.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-29.
//

#ifndef EntityManager_hpp
#define EntityManager_hpp

#include <stdio.h>
#include "Game.hpp"

class Entity;

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager {

public:
    EntityManager();
    ~EntityManager();
    
    std::shared_ptr<Entity> addEntity(const std::string& tag, std::vector<char*> textureSheet);
    // this kind of parameter above is a promise that the param won't be modified
    
    EntityVector& getEntities();
    EntityVector& getEntities(const std::string& tag);
    
    void entityUpdate(); // delayed update for iterator invalidation check, call first at new frame
    
private:
    EntityVector entities_;
    EntityMap entityMap_;
    size_t totalEntities_;
    
    EntityVector entitiesToAdd_;
    
};

#endif /* EntityManager_hpp */
