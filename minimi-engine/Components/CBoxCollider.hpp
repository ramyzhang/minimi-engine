//
//  CBoxCollider.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-09-20.
//

#ifndef CBoxCollider_hpp
#define CBoxCollider_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Component.hpp"

class CBoxCollider : public Component {
public:
    CBoxCollider() {};
    ~CBoxCollider() {};
    
    CBoxCollider(const SDL_Rect& c) : collider(c) {};
    
    SDL_Rect collider;
};

#endif /* CBoxCollider_hpp */
