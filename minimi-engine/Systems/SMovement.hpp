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
#include "Entity.hpp"
#include "Vec2.hpp"
#include "Game.hpp"

void sMovement(std::shared_ptr<Entity> entityToMove);
void sMovePlayer(std::shared_ptr<Entity> player);

#endif /* SMovement_hpp */
