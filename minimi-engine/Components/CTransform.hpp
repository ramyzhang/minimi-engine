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

class CTransform : public Component {
public:
    float pos_x = 0.0;
    float pos_y = 0.0;
    
    float velocity_x = 0.0;
    float velocity_y = 0.0;
    
    CTransform() {};
    CTransform(const float& p_x, const float& p_y, const float& v_x, const float& v_y)
    : pos_x(p_x), pos_y(p_y), velocity_x(v_x), velocity_y(v_y) {}
};

#endif /* CTransform_hpp */
