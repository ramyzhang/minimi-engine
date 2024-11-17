//
//  SRenderer.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#include "SRenderer.hpp"

void SRenderer::update() {
    SDL_RenderClear(renderer_);
    // bgTileMap->renderMap();
    updateCamera();
    
    for (auto& e : em_->getEntities()) {
        if (e->cSprite && e->cTransform) {
            draw(e);
        }
    }
    
    SDL_RenderPresent(renderer_);
}

bool SRenderer::init() {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    printf("SDL initialized!\n");
    
    
    // Create window
    window_ = SDL_CreateWindow("Minimi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    if (window_ == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    // Create renderer
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
            
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    
    background_ = loadTexture("background.png");
    
    return true;
}

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
    
    // Assign all the relevant variables
    Vec2 position = e->cTransform->pos;
    int width = e->cSprite->getWidth();
    int height = e->cSprite->getHeight();
    SDL_RendererFlip flip = e->cTransform->flip;
    double angle = e->cTransform->degrees;
    int x = static_cast<int>(position.x) - camera_.x;
    int y = static_cast<int>(position.y) - camera_.y;

    // Defines the rendering space to which we want to render to the screen
    SDL_Rect renderQuad = { x, y, width, height };
    
    SDL_SetTextureScaleMode(e->cSprite->texture, SDL_ScaleModeNearest); // since this is a pixel game
    
    SDL_Rect* currentClip = NULL;
    if (e->cAnimator) currentClip = &e->cAnimator->getSpriteClips()->at(e->cAnimator->getCurrentFrame());
    
    SDL_Point* centerOfRotation = NULL;
    if (!(e->cTransform->center.x == 0 && e->cTransform->center.y == 0)) centerOfRotation = &e->cTransform->center;
    
    SDL_RenderCopyEx(renderer_, e->cSprite->texture, currentClip, &renderQuad, angle, centerOfRotation, flip);
    
#if (DEBUG == 1)
    if (e->cBoxCollider) {
        SDL_SetRenderDrawColor(renderer_, 200, 200, 255, 255);
        SDL_Rect collider = e->cBoxCollider->collider;
        collider.x -= camera_.x;
        collider.y -= camera_.y;
        SDL_RenderDrawRect(renderer_, &collider);
    }
#endif
};

void SRenderer::draw(SDL_Texture* texture,
                     SDL_Rect* srcRect,
                     SDL_Rect* destRect) {
    SDL_RenderCopy(renderer_, texture, srcRect, destRect);
};

void SRenderer::updateCamera() {
    std::shared_ptr<Entity> player;
    if (em_->getEntities("Player").size() > 0) {
        player = em_->getEntities("Player")[0];
    } else {
        printf("Player character doesn't exist. Aborting.\n");
        return;
    }
    
    camera_.x = (player->cTransform->pos.x + player->cSprite->getWidth() / 2) - SCREEN_WIDTH / 2;
    camera_.y = (player->cTransform->pos.y + player->cSprite->getHeight() / 2) - SCREEN_HEIGHT / 2;

    // Check bounds
    if (camera_.x < 0) {
        camera_.x = 0;
    } else if (camera_.x > MAP_WIDTH - SCREEN_WIDTH) {
        camera_.x = MAP_WIDTH - SCREEN_WIDTH;
    }
    
    if (camera_.y < 0) {
        camera_.y = 0;
    } else if (camera_.y > MAP_HEIGHT - SCREEN_HEIGHT) {
        camera_.y = MAP_HEIGHT - SCREEN_HEIGHT;
    }
    
    draw(background_, &camera_, &map_); // update background clip for the camera
}

void SRenderer::free(std::shared_ptr<CSprite> sprite) {
    SDL_DestroyTexture(sprite->texture);
}

void SRenderer::clean() {
    SDL_DestroyRenderer(renderer_);
    renderer_ = NULL;
    SDL_DestroyWindow(window_);
    window_ = NULL;
}
