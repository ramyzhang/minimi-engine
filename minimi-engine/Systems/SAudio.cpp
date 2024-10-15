//
//  SAudio.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-15.
//

#include "SAudio.hpp"

void SAudio::loadAudio() {
    music_ = Mix_LoadMUS( "cupid_theme.wav" );
    if (music_ == NULL) {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        return;
    }
    
    // TODO: make SFX
}

void SAudio::startMusic() {
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(music_, -1 ); // -1 means to loop until stopped
    } else if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }
}

void SAudio::stopMusic() {
    if (Mix_PausedMusic() != 1)
    {
        Mix_PauseMusic();
    }
}

void SAudio::playAudio(SoundEffect audio) {
    switch (audio) {
        case DAMAGE: Mix_PlayChannel(-1, damage_, 0); break;
        case LOVE: Mix_PlayChannel(-1, love_, 0); break;
        case UI: Mix_PlayChannel(-1, ui_, 0); break;
        case SHOOT: Mix_PlayChannel(-1, shoot_, 0); break;
        case DEATH: Mix_PlayChannel(-1, death_, 0); break;
        default: break;
    }
}

void SAudio::freeAudio() {
    // Free the sound effects
    Mix_FreeChunk(damage_);
    Mix_FreeChunk(love_);
    Mix_FreeChunk(ui_);
    Mix_FreeChunk(shoot_);
    Mix_FreeChunk(death_);
    damage_ = NULL;
    love_ = NULL;
    ui_ = NULL;
    shoot_ = NULL;
    death_ = NULL;
    
    // Free the music
    Mix_FreeMusic(music_);
    music_ = NULL;
}
