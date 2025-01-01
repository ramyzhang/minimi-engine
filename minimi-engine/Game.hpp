//
//  Game.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-22.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "Scene.hpp"
#include "Component.hpp"
#include "EntityManager.hpp"
#include "Entity.hpp"
#include "SystemIncludes.h"

class Game {
public:
    Game();
    ~Game(); // deconstructor
    
    void init();
    void update(); // go through all the game objects and update them all
    void render();
    void clean(); // do memory management and clear the game
    
    bool isRunning() { return isRunning_; }; // is the game running?
    
    std::unordered_map<std::string, Scene *> Scene;
    std::string currentScene;
    
    static EntityManager *entityManager;
    
    // systems!
    static SRenderer *sRenderer;
    static SSpawner *sSpawner;
    static SAudio *sAudio;
    static SMovement *sMovement;
    static SCollision *sCollision;
    static SInput *sInput;
    static SAnimation *sAnimation;
    static SNPC *sNPC;
    
private:
    int  count_;
    bool isRunning_;
    bool isPaused_;
    
    void coreUpdate();
    void coreRender();
    
    SDL_Window *window_;
};

#endif /* Game_hpp */
