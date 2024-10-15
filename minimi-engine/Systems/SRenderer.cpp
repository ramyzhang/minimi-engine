//
//  SRenderer.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#include "SRenderer.hpp"

/** Load a .png file onto a texture. */
SDL_Texture* SRenderer::loadTexture(const char* fileName) {
    SDL_Surface *tempSurface = IMG_Load(fileName);
    if (tempSurface == NULL) {
        printf("Couldn't load image! SDL_Image error: %s\n", IMG_GetError());
        return NULL;
    }
    
    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer_, tempSurface);
    if (newTexture == NULL) {
        printf("TempSurface could not be created! SDL_image Error: %s\n", SDL_GetError());
        return NULL;
    }
    
    // Free the surface, as it is no longer needed
    SDL_FreeSurface(tempSurface);
    
    return newTexture;
};

/** Render a sprite. */
void SRenderer::draw(std::shared_ptr<Entity> e) {
    if (!e->cTransform || !e->cSprite) {
        printf("Tried to draw an entity with no transform or sprite!");
        return;
    }
    
    Vec2 position = e->cTransform->pos;
    int width = e->cSprite->getWidth();
    int height = e->cSprite->getHeight();
    SDL_RendererFlip flip = e->cTransform->flip;
    double angle = e->cTransform->degrees;
    
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);

    // Defines the rendering space to which we want to render to the screen
    SDL_Rect renderQuad = { x, y, width, height };
    
    SDL_SetTextureScaleMode(e->cSprite->texture, SDL_ScaleModeBest);
    
    SDL_Rect* currentClip = NULL;
    if (e->cAnimator) currentClip = &e->cAnimator->getSpriteClips()->at(e->cAnimator->getCurrentFrame());
    
    SDL_Point* centerOfRotation = NULL;
    if (!(e->cTransform->center.x == 0 && e->cTransform->center.y == 0)) centerOfRotation = &e->cTransform->center;
    
    SDL_RenderCopyEx(renderer_, e->cSprite->texture, currentClip, &renderQuad, angle, centerOfRotation, flip);
    
#if (DEBUG ==1)
    if (e->cBoxCollider) {
        SDL_SetRenderDrawColor(renderer_, 200, 200, 255, 255);
        SDL_RenderDrawRect(renderer_, &e->cBoxCollider->collider);
    }
#endif
};

void SRenderer::draw(SDL_Texture* texture,
                     SDL_Rect* srcRect,
                     SDL_Rect* destRect) {
    SDL_RenderCopy(renderer_, texture, srcRect, destRect);
};

void SRenderer::free(std::shared_ptr<CSprite> sprite) {
    SDL_DestroyTexture(sprite->texture);
}
