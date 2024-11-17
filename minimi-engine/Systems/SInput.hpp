//
//  SInput.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-04.
//

#ifndef SInput_hpp
#define SInput_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Vec2.hpp"

enum MouseEvent {
    MOUSE_DOWN,
    MOUSE_UP,
    MOUSE_NEUTRAL
};

struct MouseInputs {
    MouseEvent mouse = MOUSE_NEUTRAL;
    Vec2 pos = { 0.0, 0.0 };
};

enum GameState {
    QUIT,
    PAUSE,
    PLAYING,
};

class SInput {
public:
    SInput() {};
    ~SInput() {};
    
    Vec2 getMovementInputs() const { return *(moveInputs_); };
    MouseInputs getMouseInputs() const { return *(mouseInputs_); };
    
    GameState update(bool paused);

private:
    Vec2 *moveInputs_ = new Vec2(0, 0);
    MouseInputs *mouseInputs_ = new MouseInputs();
};

#endif /* SInput_hpp */
