//
//  CPhysics.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-11-17.
//

#ifndef CPhysics_hpp
#define CPhysics_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Component.hpp"

class CPhysics : public Component {
public:
    CPhysics() {};
    ~CPhysics() {};
    
    CPhysics(float f) : friction(f) {};
    
    float friction = 1;
};

#endif /* CPhysics_hpp */
