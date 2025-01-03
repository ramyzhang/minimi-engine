//
//  SInput.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#include "SInput.hpp"

/** Handle events in the game. This should be run inside the game loop. */
GameState SInput::update(bool paused) {
    GameState res = paused ? PAUSE : PLAYING;
    SDL_Event e;

    // Continuing polling events and handling them until there are no more
    mouseInputs_->mouse = MOUSE_NEUTRAL; // reset mouse
    while (SDL_PollEvent(&e) != 0) {
        // ------ EXIT ------
        if (e.type == SDL_QUIT) {
            return QUIT;
        }
        
        // ------ KEYS ------
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (!currentKeyStates[SDL_SCANCODE_P] && paused) {
            return PAUSE;
        }
        
        if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            if (currentKeyStates[SDL_SCANCODE_P] && !paused) {
                return PAUSE;
            } else if (currentKeyStates[SDL_SCANCODE_P] && paused) {
                res = PLAYING;
            }
            // When a key is pressed down or released
            moveInputs_->y = (currentKeyStates[SDL_SCANCODE_UP] ? -1 : (currentKeyStates[SDL_SCANCODE_DOWN] ? 1 : 0));
            moveInputs_->x = (currentKeyStates[SDL_SCANCODE_LEFT] ? -1 : (currentKeyStates[SDL_SCANCODE_RIGHT] ? 1 : 0));
        }
        
        // ------ MOUSE ------
        if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
            // Get position of mouse
            int x, y;
            SDL_GetMouseState( &x, &y );
            mouseInputs_->pos = { static_cast<float>(x), static_cast<float>(y) };
             
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                mouseInputs_->mouse = MOUSE_DOWN;
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                mouseInputs_->mouse = MOUSE_UP;
            }
        }
    }
    
    return res;
};
