//
//  CNPC.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-12-05.
//

#ifndef CNPC_hpp
#define CNPC_hpp

#include <stdio.h>
#include "Component.hpp"
#include "Vec2.hpp"

enum NPCState {
    ATTACKING,
    SEARCHING,
    LOVELOCKED,
    FADING
};

class CNPC : public Component {
public:
    CNPC() {};
    
    NPCState state = ATTACKING;
    
    // if this is an npc, set the target to move towards
    void setTarget(Vec2 target) { target_ = target; };
    Vec2 getTarget() { return target_; };
    
private:
    Vec2 target_;
};

#endif /* CNPC_hpp */
