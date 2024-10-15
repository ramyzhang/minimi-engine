//
//  CTransform.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-09-20.
//

#ifndef CTransform_hpp
#define CTransform_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Component.hpp"
#include "Vec2.hpp"

class CTransform : public Component {
public:
    CTransform() {};
    CTransform(const float& s,
               const Vec2& p,
               const Vec2& v,
               const double& d,
               const SDL_RendererFlip& f) : speed(s), pos(p), velocity(v), degrees(d), flip(f) {};
    
    float speed = 1.0;
    Vec2 pos = { 0.0, 0.0 };
    Vec2 velocity = { 0.0, 0.0 };
    double degrees = 0.0; // degrees rotated
    SDL_Point center = { 0, 0 }; // center of rotation
    SDL_RendererFlip flip = SDL_FLIP_NONE; // all my sprites are loaded in facing right
    
    // if this is an npc, set the target to move towards
    void setTarget(Vec2 target) { target_ = target; };
    Vec2 getTarget() { return target_; };
    
private:
    Vec2 target_;
};

#endif /* CTransform_hpp */
