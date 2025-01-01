//
//  CPlayer.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-12-05.
//

#ifndef CPlayer_hpp
#define CPlayer_hpp

#include <stdio.h>
#include "Component.hpp"

class CPlayer : public Component {
public:
    CPlayer() {};
    
    int maxHealth = 5;
    
    int currHealth = 5;
};

#endif /* CPlayer_hpp */
