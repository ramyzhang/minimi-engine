//
//  Level.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-11-17.
//

#ifndef Level_hpp
#define Level_hpp

#include <stdio.h>

enum LevelState {
    LEVEL_CURRENT,
    LEVEL_GONEXT,
};

class Level {
    Level() {};
    ~Level() {};
    
    Level(LevelState ls, const char* ltgt) : state(ls), levelToGoTo(ltgt) {};
    
    LevelState state;
    const char* levelToGoTo;
    
    virtual void Init() = 0;
    virtual void Spawn() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
};

#endif /* Level_hpp */
