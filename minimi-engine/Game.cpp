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
Inputs Game::inputs_;

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
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    
    // Create player entity!
    player = entityManager->addEntity("Default");
    SDL_Texture* cupid_texture = TextureManager::loadTexture("cupid_idle.png");
    
    std::vector<SDL_Rect> cupid_clips;
    for (int i = 0; i < 8; i++) {
        SDL_Rect clip = { i * 128, 0, 128, 128 };
        cupid_clips.push_back(clip);
    }
    
    Vec2 cupid_pos (336.0, 256.0);
    Vec2 cupid_velo (0.0, 0.0);
    
    player->cTransform = std::make_shared<CTransform>(3.0, cupid_pos, cupid_velo, 0.0, SDL_FLIP_NONE);
    player->cSprite = std::make_shared<CSprite>(cupid_texture, 128, 128);
    player->cAnimator = std::make_shared<CAnimator>(8, 8, cupid_clips);
    
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
        if (e->cSprite && e->cTransform) {
            if (e->cAnimator) {
                SDL_Rect currentClip = e->cAnimator->getSpriteClips()->at(e->cAnimator->getCurrentFrame());
                e->cAnimator->incrementFrame();
                
                TextureManager::draw(e->cSprite, e->cTransform->pos, &currentClip);
            } else {
                TextureManager::draw(e->cSprite, e->cTransform->pos, NULL);
            }
        }
    }
    
    SDL_RenderPresent(renderer_);
};

/** Memory management: clear the game, close the window. */
void Game::clean() {
    // Destroy all the textures in the scene
    for (auto & e : entityManager->getEntities()) {
        if (e->cSprite) {
            TextureManager::free(e->cSprite);
            e->cSprite = NULL;
        }
    }
    SDL_DestroyRenderer(renderer_);
    renderer_ = NULL;
    SDL_DestroyWindow(window_);
    window_ = NULL;
    IMG_Quit();
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
        } else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            // When a key is pressed down for the first time
            switch (e.key.keysym.sym) {
                case SDLK_UP: inputs_.up = GO; break;
                case SDLK_DOWN: inputs_.down = GO; break;
                case SDLK_LEFT: inputs_.left = GO; break;
                case SDLK_RIGHT: inputs_.right = GO; break;
                default: break;
            }
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            // When a key is released for the first time
            switch(e.key.keysym.sym) {
                case SDLK_UP: inputs_.up = STOP; break;
                case SDLK_DOWN: inputs_.down = STOP; break;
                case SDLK_LEFT: inputs_.left = STOP; break;
                case SDLK_RIGHT: inputs_.right = STOP; break;
                default: break;
            }
        }
    }
};

void Game::sMovement() {
    if (player->cTransform) {
        float speed = player->cTransform->speed;
        
        switch (inputs_.up) {
            case GO: player->cTransform->velocity.add(Vec2(0, -speed)); break;
            case STOP: player->cTransform->velocity.add(Vec2(0, speed)); break;
            default: break;
        }
        
        inputs_.up = NEUTRAL;
        
        switch (inputs_.down) {
            case GO: player->cTransform->velocity.add(Vec2(0, speed)); break;
            case STOP: player->cTransform->velocity.add(Vec2(0, -speed)); break;
            default: break;
        }
        
        inputs_.down = NEUTRAL;

        switch (inputs_.left) {
            case GO: player->cTransform->velocity.add(Vec2(-speed, 0)); break;
            case STOP: player->cTransform->velocity.add(Vec2(speed, 0)); break;
            default: break;
        }
        
        inputs_.left = NEUTRAL;

        switch (inputs_.right) {
            case GO: player->cTransform->velocity.add(Vec2(speed, 0)); break;
            case STOP: player->cTransform->velocity.add(Vec2(-speed, 0)); break;
            default: break;
        }
        
        inputs_.right = NEUTRAL;
        
        player->cTransform->pos.add(player->cTransform->velocity);
    }
}

