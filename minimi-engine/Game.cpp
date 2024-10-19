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
MovementInputs *Game::movementInputs_ = new MovementInputs();
MouseInputs *Game::mouseInputs_ = new MouseInputs();

SRenderer *Game::sRenderer = new SRenderer();
TileMap *bgTileMap; // Temporary
SSpawner *Game::sSpawner = new SSpawner(entityManager, sRenderer, 100);
SAudio *Game::sAudio = new SAudio();
SMovement *Game::sMovement = new SMovement();

/** Initialize SDL and the game window + renderer. **/
void Game::init() {
    // ------- INIT RENDERER -------
    isRunning_ = sRenderer->init();
    if (!isRunning_) return;
    
    // ------- INIT AUDIO -------
    isRunning_ = sAudio->init();
    if (!isRunning_) return;
    
    sAudio->loadAudio();
    sAudio->startMusic();
    
    // ------- INIT SPAWNER -------
    sSpawner->spawnPlayer();
    
    // ------- INIT MOVEMENT -------
    sMovement->init(entityManager, sSpawner->getPlayer(), sSpawner->getBow()); // movement system
    
    // Ignore this for now
    bgTileMap = new TileMap(sRenderer);
    
    printf("Game is running!\n");
    isRunning_ = true;
};

/** Go through all the game objects and update them all. */
void Game::update() {
    // -------- PLAYER UPDATE --------
    sMovement->movePlayer(getMovementInputs()); // Move player
    sSpawner->getPlayer()->cAnimator->incrementFrame(); // Animate player
     
    // ------- BOW UPDATE -------
    sMovement->moveBow();
    
    // ------- ARROW UPDATE -------
    if (getMouseInputs().mouse == MOUSE_UP) {
        std::shared_ptr<Entity> new_arrow = sSpawner->spawnArrow();
        sAudio->playAudio(SHOOT);
    }
    
    for (auto& e : entityManager->getEntities("Arrow")) {
        sMovement->moveArrow(e);
        float distance = e->cTransform->pos.distance(sSpawner->getPlayer()->cTransform->pos);
        if (distance > 500) {
            e->destroy();
        }
    }
    
    // -------- NPC UPDATE --------
    // Spawn an enemy
    sSpawner->spawnEnemy();
    // Iterate through NPCs
    for (auto& e : entityManager->getEntities("NPC")) {
        // -------- MOVEMENT & AI --------
        // Update transforms based on movement
        if (e->cTransform) sSpawner->updateEnemy(e);
        if (e->cTransform) sMovement->moveNPC(e);
        
        // -------- PHYSICS --------
        if (e->cBoxCollider) {
            if (checkCollision(e, sSpawner->getPlayer())) {
                sAudio->playAudio(DAMAGE);
                e->destroy();
            }
            for (auto& arrow : entityManager->getEntities("Arrow")) {
                if (arrow->cBoxCollider && checkCollision(arrow, e)) {
                    sAudio->playAudio(LOVE);
                    e->destroy();
                    arrow->destroy();
                }
            }
        }
        
        // -------- ANIMATION --------
        if (e->cAnimator) e->cAnimator->incrementFrame();
    }
    count_++;
    entityManager->entityUpdate();
};

/** Clear and re-render new screen contents for the next frame. */
void Game::render() {
    SDL_SetRenderDrawColor(sRenderer->getRenderer(), 196, 255, 239, 255);
    SDL_RenderClear(sRenderer->getRenderer());
    // bgTileMap->renderMap();
    
    for (auto& e : entityManager->getEntities()) {
        if (e->cSprite && e->cTransform) {
            sRenderer->draw(e);
        }
    }
    
    SDL_RenderPresent(sRenderer->getRenderer());
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
                case SDLK_UP: movementInputs_->up = GO; break;
                case SDLK_DOWN: movementInputs_->down = GO; break;
                case SDLK_LEFT: movementInputs_->left = GO; break;
                case SDLK_RIGHT: movementInputs_->right = GO; break;
                default: break;
            }
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            // When a key is released for the first time
            switch(e.key.keysym.sym) {
                case SDLK_UP: movementInputs_->up = STOP; break;
                case SDLK_DOWN: movementInputs_->down = STOP; break;
                case SDLK_LEFT: movementInputs_->left = STOP; break;
                case SDLK_RIGHT: movementInputs_->right = STOP; break;
                default: break;
            }
        } else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
            // Get position of mouse
            int x, y;
            SDL_GetMouseState( &x, &y );
            mouseInputs_->pos = { static_cast<float>(x), static_cast<float>(y) };
             
            mouseInputs_->mouse = MOUSE_NEUTRAL;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                mouseInputs_->mouse = MOUSE_DOWN;
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                mouseInputs_->mouse = MOUSE_UP;
            }
        }
    }
};



