//
//  main.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-15.
//

/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <stdio.h>
#include "Game.hpp"

Game *game = nullptr;

/**
while (game is running):
    handle user input
    update gameobject positions
    render changes to display
 */
int main(int argc, char* args[])
{
    const int fps = 60;
    const int frameDelay = 1000 / fps;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Minimi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    
    while (game->isRunning()) {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime); // sleep
        }
    }
    
    game->clean();
    
    return 0;
}
