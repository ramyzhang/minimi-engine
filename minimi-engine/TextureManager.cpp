//
//  TextureManager.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-23.
//

#include "TextureManager.hpp"

/** Load a .png file onto a texture. */
SDL_Texture* TextureManager::loadTexture(const char* fileName, SDL_Renderer* renderer) {
    SDL_Surface *tempSurface = IMG_Load(fileName);
    if (tempSurface == NULL) {
        printf("Couldn't load image! SDL_Image error: %s\n", IMG_GetError());
        return NULL;
    }
    
    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if (newTexture == NULL) {
        printf("TempSurface could not be created! SDL_image Error: %s\n", SDL_GetError());
        return NULL;
    }
    
    // Free the surface, as it is no longer needed
    SDL_FreeSurface(tempSurface);
    
    return newTexture;
};
