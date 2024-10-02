//
//  Game.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-22.
//

#include "Game.hpp"

Game::Game() {};
Game::~Game() {};

std::shared_ptr<Entity> player;
SDL_Renderer *Game::renderer_ = nullptr;
TileMap *bgTileMap;
EntityManager *entityManager = new EntityManager();

/** Initialize SDL and the game window + renderer. **/
void Game::init(const char* title, int xPosition, int yPosition, int width, int height, bool fullScreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning_ = false;
        return;
    }
    printf("SDL initialized!\n");
    
    // Create window
    window_ = SDL_CreateWindow("Minimi", xPosition, yPosition, width, height, fullScreen);
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
    
    // Add player entity!
    player = entityManager->addEntity("Default");
    SDL_Texture* cupid_texture = TextureManager::loadTexture("cupid_idle0.png");
    SDL_Rect cupid_srcRect;
    SDL_Rect cupid_destRect;
    cupid_srcRect.x = cupid_srcRect.y = 0;
    cupid_destRect.x = 336;
    cupid_destRect.y = 256;
    cupid_srcRect.h = cupid_srcRect.w = 64;
    cupid_destRect.h = cupid_destRect.w = 128;
    
    Vec2 cupid_pos = { 336, 256 };
    Vec2 cupid_velo = { 0, 0 };
    player->cTransform = std::make_shared<CTransform>(cupid_pos, cupid_velo);
    player->cSprite = std::make_shared<CSprite>(cupid_texture, cupid_srcRect, cupid_destRect);
    
    bgTileMap = new TileMap();
    
    printf("Game is running!\n");
    isRunning_ = true;
};

/** Go through all the game objects and update them all. */
void Game::update() {
    count_++;
    entityManager->entityUpdate();
};

/** Clear and re-render new screen contents for the next frame. */
void Game::render() {
    SDL_RenderClear(renderer_);
    bgTileMap->renderMap();
    
    for (auto& e : entityManager->getEntities()) {
        if (e->cSprite) {
            TextureManager::draw(e->cSprite->texture, e->cSprite->srcRect, e->cSprite->destRect);
        }
    }
    
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

    // Continuing polling events and handling them until there are no more
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            isRunning_ = false;
            break;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    break;

                case SDLK_DOWN:
                    break;

                case SDLK_LEFT:
                    break;

                case SDLK_RIGHT:
                    break;

                default:
                    break;
            }
        }
    }
};

