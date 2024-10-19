//
//  SCollision.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#ifndef SCollision_hpp
#define SCollision_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "EntityManager.hpp"
#include "SSubject.hpp"

class SCollision : public SSubject {
public:
    SCollision () {};
    ~SCollision () {};
    
    SCollision(EntityManager* em) : em_(em) {};
    
    void init(std::shared_ptr<Entity> player) { player_ = player; };
    
    void update();
    
private:
    bool checkCollision(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
    
    EntityManager* em_;
    std::shared_ptr<Entity> player_;
};

#endif /* SCollision_hpp */
