//
//  SInput.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-04.
//

#ifndef SInput_hpp
#define SInput_hpp

#include <stdio.h>

enum InputDirection {
    STOP,
    NEUTRAL,
    GO
};

struct Inputs {
    InputDirection up = NEUTRAL;
    InputDirection down = NEUTRAL;
    InputDirection left = NEUTRAL;
    InputDirection right = NEUTRAL;
};

#endif /* SInput_hpp */
