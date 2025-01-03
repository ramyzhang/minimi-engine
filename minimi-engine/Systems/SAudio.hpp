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
#include "Observer.hpp"
#include "Entity.hpp"

enum SoundEffect {
    DAMAGE,
    LOVE,
    UI,
    SHOOT,
    DEATH
};

class SAudio : public Observer {
public:
    SAudio() {};
    ~SAudio() {};
    
    virtual void onNotify(Event event, std::shared_ptr<Entity> entity) {
        switch (event) {
            case ENEMY_DIED: playAudio(LOVE); break;
            case ARROW_SHOT: playAudio(SHOOT); break;
            case PLAYER_HIT: playAudio(DAMAGE); break;
            case PLAYER_DIED: playAudio(DEATH); stopMusic(); break;
            case NPC_LOVE: break;
            default: break;
        }
    }
    
    bool init();
    
    void loadAudio();
    
    void startMusic();
    void stopMusic();
    
    void playAudio(SoundEffect audio);
    
    void clean();
    
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
