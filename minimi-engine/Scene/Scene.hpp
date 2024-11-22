//
//  Scene.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-11-17.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <string>

enum SceneState {
    SCENE_CURRENT,
    SCENE_GONEXT,
};

class Scene {
public:
    Scene() {};
    ~Scene() {};
    
    Scene(const SceneState &ls, const std::string &ltgt) : state(ls), levelToGoTo(ltgt) {};
    
    virtual void Init() = 0;
    virtual void Spawn() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
    
    SceneState state;
    std::string levelToGoTo;
};

#endif /* Scene_hpp */
