//
//  Vec2.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-09-20.
//

#ifndef Vec2_hpp
#define Vec2_hpp

#include <stdio.h>
#include <math.h>

class Vec2 {
public:
    float x;
    float y;
    
    Vec2() {};
    Vec2(float _x, float _y) : x(_x), y(_y) {};
    
    Vec2 operator + (const Vec2& rhs) const;
    
    Vec2 operator - (const Vec2& rhs) const;
    
    Vec2 operator * (const float& rhs) const;
        
    Vec2& add(const Vec2& rhs);
    
    Vec2& subtract(const Vec2& rhs);
    
    Vec2& scale(const float& rhs);
    
    Vec2& rotate(const float& deg);
    
    float distance(const Vec2& v) const;
    
    Vec2& normalize(const Vec2& v);
};

#endif /* Vec2_hpp */
