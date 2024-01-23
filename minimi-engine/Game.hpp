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
#include <math.h>
#include "TextureManager.hpp"
#include "GameObject.hpp"

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
    
private:
    bool isRunning_;
    SDL_Window *window_;
    SDL_Renderer *renderer_;
    int count_;
};

#endif /* Game_hpp */
