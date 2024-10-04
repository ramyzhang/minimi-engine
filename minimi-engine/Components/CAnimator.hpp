//
//  CAnimator.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-04.
//

#ifndef CAnimator_hpp
#define CAnimator_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <vector>
#include "Component.hpp"

class CAnimator : public Component {
public:
    CAnimator() {};
    CAnimator(const int& f,
              const int& fr,
              const std::vector<SDL_Rect>& sc) : frames_(f), frameRate_(fr), spriteClips_(sc) {};
    
    int getNumberOfFrames() { return frames_; };
    void setNumberOfFrames(int num) { frames_ = num; };
    
    void setFrameRate(int rate) { frameRate_ = rate; };
    
    int getCurrentFrame() { return currFrame_; };
    void incrementFrame();
    
    void setSpriteClips(std::vector<SDL_Rect> sc) { spriteClips_ = sc; };
    std::vector<SDL_Rect>* getSpriteClips() { return &spriteClips_; };

private:
    int frames_ = 0;
    int currFrame_ = 0;
    int counter_ = 0;
    int frameRate_ = 1;
    
    std::vector<SDL_Rect> spriteClips_;
};

#endif /* CAnimator_hpp */
