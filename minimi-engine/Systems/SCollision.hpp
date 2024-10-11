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
#include "Entity.hpp"

bool checkCollision(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);

#endif /* SCollision_hpp */
