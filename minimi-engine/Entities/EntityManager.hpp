//
//  EntityManager.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-29.
//

#ifndef EntityManager_hpp
#define EntityManager_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "Entity.hpp"

#define MAX_ENTITIES 200

class Entity;

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager {

public:
    EntityManager();
    ~EntityManager();
    
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    // this kind of parameter above is a promise that the param won't be modified
    
    EntityVector& getEntities();
    EntityVector& getEntities(const std::string& tag);
    
    size_t getNumEntities() { return totalEntities_; };
    
    void entityUpdate(); // delayed update for iterator invalidation check, call first at new frame
    
    void changeTag(std::string newTag, std::shared_ptr<Entity> e);
    
private:
    EntityVector entities_;
    EntityMap entityMap_;
    size_t totalEntities_;
    
    EntityVector entitiesToAdd_;
};

#endif /* EntityManager_hpp */
