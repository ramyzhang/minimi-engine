//
//  SMovement.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-04.
//

#ifndef SMovement_hpp
#define SMovement_hpp

#include <stdio.h>
#include "SInput.hpp"
#include "EntityManager.hpp"
#include "Vec2.hpp"
#include "Utils.hpp"

class SMovement {
public:
    SMovement() {};
    ~SMovement() {};
    
    void init(EntityManager* em, std::shared_ptr<Entity> p, std::shared_ptr<Entity> b) {
        em_ = em;
        player_ = p;
        bow_ = b;
    };
    
    void update(MovementInputs *inputs);

private:
    void moveNPC(std::shared_ptr<Entity> entityToMove);
    void movePlayer(MovementInputs *inputs);
    void moveBow();
    void moveArrow(std::shared_ptr<Entity> arrow);
    
    EntityManager* em_;
    std::shared_ptr<Entity> player_;
    std::shared_ptr<Entity> bow_;
};

#endif /* SMovement_hpp */
