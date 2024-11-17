//
//  Game.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-22.
//

#include "Game.hpp"

Game::Game() {};
Game::~Game() {};

EntityManager *Game::entityManager = new EntityManager();

SRenderer *Game::sRenderer = new SRenderer(entityManager);
SSpawner *Game::sSpawner = new SSpawner(entityManager, sRenderer, 100);
SAudio *Game::sAudio = new SAudio();
SMovement *Game::sMovement = new SMovement();
SCollision *Game::sCollision = new SCollision(entityManager);
SInput *Game::sInput = new SInput();

/** Initialize SDL and the game window + renderer. **/
void Game::init() {
    isRunning_ = sRenderer->init();
    if (!isRunning_) return;
    
    isRunning_ = sAudio->init();
    if (!isRunning_) return;
    sAudio->loadAudio();
    sAudio->startMusic();
    
    sSpawner->spawnPlayer();
    sSpawner->addObserver(sAudio);
    
    sMovement->init(entityManager, sSpawner->getPlayer(), sSpawner->getBow()); // movement system
    
    sCollision->init(sSpawner->getPlayer());
    sCollision->addObserver(sAudio);
    
    printf("Game is running!\n");
    isRunning_ = true;
    isPaused_ = false;
};

/** Go through all the game entities and update them all. */
void Game::update() {
    switch (sInput->update(isPaused_)) {
        case QUIT:
            isRunning_ = false;
            break;
        case PAUSE:
            isPaused_ = true; 
            break;
        case PLAYING:
            isPaused_ = false; 
            break;
        default:
            break;
    }
    
    if (!isPaused_) {
        sMovement->update(sInput->getMovementInputs());
        sSpawner->update(sInput->getMouseInputs());
        sCollision->update();
    }
    
    sSpawner->getPlayer()->cAnimator->incrementFrame(); // Animate player
    for (auto& e : entityManager->getEntities("NPC")) {
        if (e->cAnimator) e->cAnimator->incrementFrame();
    }
    
    count_++;
    entityManager->entityUpdate();
};

/** Clear and re-render new screen contents for the next frame. */
void Game::render() {
    sRenderer->update();
};

/** Memory management: clear the game, close the window. */
void Game::clean() {
    // Destroy all the textures in the scene
    for (auto & e : entityManager->getEntities()) {
        if (e->cSprite) {
            sRenderer->free(e->cSprite);
            e->cSprite = NULL;
        }
    }
    
    sAudio->freeAudio();
    sRenderer->clean();
    
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    printf("Cleaned game.\n");
};




