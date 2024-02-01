//
//  Game.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-22.
//

#include "Game.hpp"

Game::Game() {};
Game::~Game() {};

Entity *player;
SDL_Renderer *Game::renderer_ = nullptr;
TileMap *bgTileMap;

/** Initialize SDL and the game window + renderer. **/
void Game::init(const char* title, int xPosition, int yPosition, int width, int height, bool fullScreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning_ = false;
        return;
    }
    printf("SDL initialized!\n");
    
    // Create window
    window_ = SDL_CreateWindow("Minimi Engine", xPosition, yPosition, width, height, fullScreen);
    if (window_ == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning_ = false;
        return;
    }
    
    // Create renderer
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    if (renderer_ == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning_ = false;
        return;
    }
    
    SDL_SetRenderDrawColor(renderer_, 144, 223, 157, 255);
    
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return;
    }
    
    std::vector<char*> frameFiles = {
        (char*)"cupid_idle0.png",
        (char*)"cupid_idle1.png",
        (char*)"cupid_idle2.png",
        (char*)"cupid_idle3.png",
        (char*)"cupid_idle4.png",
        (char*)"cupid_idle5.png",
        (char*)"cupid_idle6.png",
        (char*)"cupid_idle7.png"
    };
    
    player = new Entity(0, "Default", frameFiles, 0, 0);
    
    bgTileMap = new TileMap();
    
    printf("Game is running!\n");
    isRunning_ = true;
};

/** Go through all the game objects and update them all. */
void Game::update() {
    count_++;
    player->update();
};

/** Clear and re-render new screen contents for the next frame. */
void Game::render() {
    SDL_RenderClear(renderer_);
    bgTileMap->renderMap();
    player->render();
    SDL_RenderPresent(renderer_);
};

/** Memory management: clear the game, close the window. */
void Game::clean() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
    printf("Cleaned game.\n");
};

/** Handle events in the game. This should be run inside the game loop. */
void Game::handleEvents() {
    SDL_Event e;
    SDL_PollEvent(&e);
    
    switch (e.type) {
        case SDL_QUIT:
            isRunning_ = false;
            break;
            
        default:
            // printf("This event hasn't been handled yet: %d\n", e.type);
            break;
    }
};

