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

typedef std::vector<SDL_Rect> Clip;
typedef std::vector<std::vector<SDL_Rect>> ClipVector;

class CAnimator : public Component {
public:
    CAnimator() {};
    CAnimator(const int& f,
              const int& fr,
              const ClipVector& sc) : frames_(f), frameRate_(fr), spriteClips_(sc) {};
    
    int getNumberOfFrames() { return frames_; };
    void setNumberOfFrames(int num) { frames_ = num; };
    
    void setFrameRate(int rate) { frameRate_ = rate; };
    
    int getCurrentFrame() { return currFrame_; };
    void incrementFrame();
    
    void setSpriteClip(int index);
    Clip* getSpriteClip() { return &spriteClips_[currClip_]; };
    int getClipIndex() { return currClip_; };
    
    void setLooping(bool loop) { isLooping = loop; };

private:
    int frames_ = 0;
    int currFrame_ = 0;
    int counter_ = 0;
    int frameRate_ = 1;
    
    int currClip_ = 0;
    
    bool isLooping = true;
    
    ClipVector spriteClips_;
};

#endif /* CAnimator_hpp */
