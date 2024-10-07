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
    float speed = 1.0;
    
    Vec2 pos = { 0.0, 0.0 };
    
    Vec2 velocity = { 0.0, 0.0 };
    
    double degrees = 0.0;
    
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    
    CTransform() {};
    CTransform(const float& s,
               const Vec2& p,
               const Vec2& v,
               const double& d,
               const SDL_RendererFlip& f) : speed(s), pos(p), velocity(v), degrees(d), flip(f) {};
    
    void setTarget(Vec2 target) { target_ = target; };
    Vec2 getTarget() { return target_; };
    
private:
    Vec2 target_;
};

#endif /* CTransform_hpp */
