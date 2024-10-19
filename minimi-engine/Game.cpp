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
EntityManager *Game::entityManager = new EntityManager();
SDL_Renderer *Game::renderer = nullptr;
MovementInputs Game::movementInputs_;
MouseInputs Game::mouseInputs_;

SRenderer *sRenderer; // TODO: do something about this...
TileMap *bgTileMap; // Temporary
SSpawner *sSpawner; // TODO: do something about this...
SAudio *sAudio; // TODO: do something about this...
SMovement *sMovement; // TODO: do something about this...

/** Initialize SDL and the game window + renderer. **/
void Game::init(const char* title, int xPosition, int yPosition, int width, int height, bool fullScreen) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    
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
    renderer = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning_ = false;
        return;
    }
        
    SDL_SetRenderDrawColor(renderer, 196, 255, 239, 255);
    
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return;
    }
    
    // Initialize SDL_Mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
    
    // Create player entity and render initial scene!
    sRenderer = new SRenderer(renderer); // renderer
    
    sAudio = new SAudio(); // audio player
    sAudio->loadAudio();
    sAudio->startMusic();
    
    sSpawner = new SSpawner(entityManager, sRenderer, 100); // spawner
    player = sSpawner->spawnPlayer();
    
    sMovement = new SMovement(player, sSpawner->getBow()); // movement system
    
    // Ignore this for now
    bgTileMap = new TileMap(sRenderer);
    
    printf("Game is running!\n");
    isRunning_ = true;
};

/** Go through all the game objects and update them all. */
void Game::update() {
    // -------- PLAYER UPDATE --------
    sMovement->movePlayer(player, getMovementInputs()); // Move player
    player->cAnimator->incrementFrame(); // Animate player
     
    // ------- BOW UPDATE -------
    sMovement->moveBow(sSpawner->getBow(), player);
    
    // ------- ARROW UPDATE -------
    if (getMouseInputs().mouse == MOUSE_UP) {
        std::shared_ptr<Entity> new_arrow = sSpawner->spawnArrow();
        sAudio->playAudio(SHOOT);
    }
    
    for (auto& e : entityManager->getEntities("Arrow")) {
        sMovement->moveArrow(e, sSpawner->getBow(), player);
        float distance = e->cTransform->pos.distance(player->cTransform->pos);
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
            if (checkCollision(e, player)) {
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
    SDL_SetRenderDrawColor(renderer, 196, 255, 239, 255);
    SDL_RenderClear(renderer);
    // bgTileMap->renderMap();
    
    for (auto& e : entityManager->getEntities()) {
        if (e->cSprite && e->cTransform) {
            sRenderer->draw(e);
        }
    }
    
    SDL_RenderPresent(renderer);
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
    
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window_);
    window_ = NULL;
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
                case SDLK_UP: movementInputs_.up = GO; break;
                case SDLK_DOWN: movementInputs_.down = GO; break;
                case SDLK_LEFT: movementInputs_.left = GO; break;
                case SDLK_RIGHT: movementInputs_.right = GO; break;
                default: break;
            }
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            // When a key is released for the first time
            switch(e.key.keysym.sym) {
                case SDLK_UP: movementInputs_.up = STOP; break;
                case SDLK_DOWN: movementInputs_.down = STOP; break;
                case SDLK_LEFT: movementInputs_.left = STOP; break;
                case SDLK_RIGHT: movementInputs_.right = STOP; break;
                default: break;
            }
        } else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
            // Get position of mouse
            int x, y;
            SDL_GetMouseState( &x, &y );
            mouseInputs_.pos = { static_cast<float>(x), static_cast<float>(y) };
             
            mouseInputs_.mouse = MOUSE_NEUTRAL;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                mouseInputs_.mouse = MOUSE_DOWN;
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                mouseInputs_.mouse = MOUSE_UP;
            }
        }
    }
};



