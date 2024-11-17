//
//  Entity.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-31.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <math.h>
#include <string>
#include "CTransform.hpp"
#include "CSprite.hpp"
#include "CBoxCollider.hpp"
#include "CAnimator.hpp"
#include "CPhysics.hpp"

class Component;

class Entity {
    
public:
    friend class EntityManager; // only allow EntityManager to access private variables
    
    std::string getTag();
    bool isActive();
    
    void destroy();
    
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CSprite> cSprite;
    std::shared_ptr<CBoxCollider> cBoxCollider;
    std::shared_ptr<CAnimator> cAnimator;
    std::shared_ptr<CPhysics> cPhysics;
    
private:
    // Constructor is private; only EntityManager can make new Entities
    Entity(const size_t id, const std::string& tag);
    
    size_t      id_     = 0;
    std::string tag_    = "Default";
    bool        active_ = true;
    
};

#endif /* Entity_hpp */
