//
//  TextureManager.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-23.
//

#include "TextureManager.hpp"

/** Load a .png file onto a texture. */
SDL_Texture* TextureManager::loadTexture(const char* fileName) {
    SDL_Surface *tempSurface = IMG_Load(fileName);
    if (tempSurface == NULL) {
        printf("Couldn't load image! SDL_Image error: %s\n", IMG_GetError());
        return NULL;
    }
    
    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(Game::renderer_, tempSurface);
    if (newTexture == NULL) {
        printf("TempSurface could not be created! SDL_image Error: %s\n", SDL_GetError());
        return NULL;
    }
    
    // Free the surface, as it is no longer needed
    SDL_FreeSurface(tempSurface);
    
    return newTexture;
};

/** Render a texture. */
void TextureManager::draw(std::shared_ptr<CSprite> sprite, Vec2 position, SDL_Rect* clip) {
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);
    
    // Defines the rendering space to which we want to render to the screen
    SDL_Rect renderQuad = { x, y, sprite->getWidth(), sprite->getHeight() };
    
    // If clip is not null, then we only want to render a portion of the spritesheet
    // Otherwise, just render the whole texture
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    SDL_RenderCopy(Game::renderer_, sprite->texture, clip, &renderQuad);
};

void TextureManager::drawTile(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect) {
    SDL_RenderCopy(Game::renderer_, texture, srcRect, destRect);
};

void TextureManager::free(std::shared_ptr<CSprite> sprite) {
    SDL_DestroyTexture(sprite->texture);
}
