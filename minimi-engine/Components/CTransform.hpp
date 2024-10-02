//
//  CTransform.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-09-20.
//

#ifndef CTransform_hpp
#define CTransform_hpp

#include <stdio.h>
#include "Component.hpp"
#include "Vec2.hpp"

class CTransform : public Component {
public:
    Vec2 pos = { 0.0, 0.0 };
    
    Vec2 velocity = { 0.0, 0.0 };
    
    CTransform() {};
    CTransform(const Vec2& p, const Vec2& v) : pos(p), velocity(v) {}
};

#endif /* CTransform_hpp */
