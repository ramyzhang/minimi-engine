//
//  SSpawner.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#ifndef SSpawner_hpp
#define SSpawner_hpp

#include <stdio.h>
#include <math.h>
#include "EntityManager.hpp"
#include "SRenderer.hpp"
#include "Utils.hpp"
#include "Vec2.hpp"

const float NPC_SPEED = 1;

class SSpawner {
public:
    SSpawner() {};
    ~SSpawner() {};
    
    SSpawner(EntityManager* em,
             SRenderer* r,
             const int& sr) : entityManager_(em), renderer_(r), spawnRate_(sr) {};
    
    std::shared_ptr<Entity> getPlayer() { return player_; };
    std::shared_ptr<Entity> getBow() { return bow_; };
    
    std::shared_ptr<Entity> spawnPlayer();
    std::shared_ptr<Entity> spawnEnemy();
    std::shared_ptr<Entity> spawnArrow(bool isInit = false);
    
    void updateEnemy(std::shared_ptr<Entity> npc);
    
private:
    EntityManager* entityManager_;
    SRenderer* renderer_;
    std::shared_ptr<Entity> player_; // Needs player entity to be able to calculate initial pos
    std::shared_ptr<Entity> bow_; // Needs bow entity to calculate initial arrow pos
    
    void spawnBow(); // spawnPlayer should privately call this method
    
    // Manage spawn rate
    int counter_ = 0;
    int spawnRate_ = 20;
};

#endif /* SSpawner_hpp */
