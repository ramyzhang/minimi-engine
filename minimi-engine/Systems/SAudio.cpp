//
//  SAudio.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-15.
//

#include "SAudio.hpp"

bool SAudio::init() {
    // Initialize SDL_Mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    
    loadAudio();
    startMusic();
    
    return true;
}

void SAudio::loadAudio() {
    // TODO: Make audio shorter
    music_ = Mix_LoadMUS( "cupid_theme.wav" );
    if (music_ == NULL) {
        printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
        return;
    }
    
    damage_ = Mix_LoadWAV("damage.wav");
    if (damage_ == NULL) {
        printf( "Failed to load damage SFX! SDL_mixer Error: %s\n", Mix_GetError() );
        return;
    }
    Mix_VolumeChunk(damage_, 60);
    
    death_ = Mix_LoadWAV("death.wav");
    if (death_ == NULL) {
        printf( "Failed to load death SFX! SDL_mixer Error: %s\n", Mix_GetError() );
        return;
    }
    
    love_ = Mix_LoadWAV("love.wav");
    if (love_ == NULL) {
        printf( "Failed to load love SFX! SDL_mixer Error: %s\n", Mix_GetError() );
        return;
    }
    Mix_VolumeChunk(love_, 30);
    
    shoot_ = Mix_LoadWAV("shoot.wav");
    if (shoot_ == NULL) {
        printf( "Failed to load shoot SFX! SDL_mixer Error: %s\n", Mix_GetError() );
        return;
    }
    
    ui_ = Mix_LoadWAV("ui.wav");
    if (ui_ == NULL) {
        printf( "Failed to load UI SFX! SDL_mixer Error: %s\n", Mix_GetError() );
        return;
    }
}

void SAudio::startMusic() {
    if (Mix_PlayingMusic() == 0)
    {
        Mix_FadeInMusic(music_, -1, 5000); // -1 means to loop until stopped
    } else if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }
}

void SAudio::stopMusic() {
    if (Mix_PausedMusic() != 1)
    {
        Mix_FadeOutMusic(500);
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
