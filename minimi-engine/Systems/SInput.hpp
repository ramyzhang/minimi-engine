//
//  SInput.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-04.
//

#ifndef SInput_hpp
#define SInput_hpp

#include <stdio.h>
#include "Vec2.hpp"

enum InputEvent {
    STOP,
    NEUTRAL,
    GO
};

enum MouseEvent {
    MOUSE_DOWN,
    MOUSE_UP,
    MOUSE_NEUTRAL
};

struct MovementInputs {
    InputEvent up = NEUTRAL;
    InputEvent down = NEUTRAL;
    InputEvent left = NEUTRAL;
    InputEvent right = NEUTRAL;
};

struct MouseInputs {
    MouseEvent mouse = MOUSE_NEUTRAL;
    Vec2 pos = { 0.0, 0.0 };
};

#endif /* SInput_hpp */
