//
//  SAudio.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-15.
//

#ifndef SAudio_hpp
#define SAudio_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

enum SoundEffect {
    DAMAGE,
    LOVE,
    UI,
    SHOOT,
    DEATH
};

class SAudio {
public:
    SAudio() {};
    ~SAudio() {};
    
    void loadAudio();
    
    void startMusic();
    void stopMusic();
    
    void playAudio(SoundEffect audio);
    
    void freeAudio();
    
private:
    // The music that will be played
    Mix_Music* music_ = NULL;
    
    // TODO: turn this into a map?
    Mix_Chunk* damage_ = NULL;
    Mix_Chunk* love_ = NULL;
    Mix_Chunk* ui_ = NULL;
    Mix_Chunk* shoot_ = NULL;
    Mix_Chunk* death_ = NULL;
};

#endif /* SAudio_hpp */
