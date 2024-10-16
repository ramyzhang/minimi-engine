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
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "SRenderer.hpp"
#include "TileMap.hpp"
#include "Component.hpp"
#include "EntityManager.hpp"
#include "Entity.hpp"
#include "SMovement.hpp"
#include "SInput.hpp"
#include "SSpawner.hpp"
#include "SCollision.hpp"
#include "SAudio.hpp"

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

class Game {
    
public:
    Game();
    ~Game(); // deconstructor
    
    void init(const char* title, int xPosition, int yPosition, int width, int height, bool fullScreen);
    void update(); // go through all the game objects and update them all
    void render();
    void clean(); // do memory management and clear the game
    void handleEvents();
    
    bool isRunning() { return isRunning_; }; // is the game running?
    static MovementInputs* getMovementInputs() { return &movementInputs_; };
    static MouseInputs getMouseInputs() {
        MouseInputs temp = mouseInputs_;
        mouseInputs_.mouse = MOUSE_NEUTRAL;
        return temp;
    };
    
    static SDL_Renderer *renderer;
    static EntityManager *entityManager;
    
private:
    int  count_;
    bool isRunning_;
    static MovementInputs movementInputs_;
    static MouseInputs mouseInputs_;
    
    SDL_Window *window_;
};

#endif /* Game_hpp */
