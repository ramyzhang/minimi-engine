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
    
    SMovement(std::shared_ptr<Entity> p, std::shared_ptr<Entity> b) : player_(p), bow_(b) {};
    
    void moveNPC(std::shared_ptr<Entity> entityToMove);
    void movePlayer(std::shared_ptr<Entity> player, MovementInputs *inputs);
    void moveBow(std::shared_ptr<Entity> bow, std::shared_ptr<Entity> player);
    void moveArrow(std::shared_ptr<Entity> arrow, std::shared_ptr<Entity> bow, std::shared_ptr<Entity> player);

private:
    std::shared_ptr<Entity> player_;
    std::shared_ptr<Entity> bow_;
};

#endif /* SMovement_hpp */
