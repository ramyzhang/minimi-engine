//
//  CoreGame.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-11-21.
//

#ifndef CoreGame_hpp
#define CoreGame_hpp

#include <stdio.h>
#include "Scene.hpp"
#include "SystemIncludes.h"

class CoreGame : public Scene {
    CoreGame() : Scene(SCENE_CURRENT, "GameOver") {};
    
    void Init() override;
//    void Spawn() override;
//    void Update() override;
//    void Exit() override;
};

#endif /* CoreGame_hpp */
