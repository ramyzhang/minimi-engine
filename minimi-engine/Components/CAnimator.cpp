//
//  CAnimator.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-04.
//

#include "CAnimator.hpp"

void CAnimator::incrementFrame(bool loop) {
    if (!loop && currFrame_ >= frames_) return;
    
    // Increment current frame based on framerate
    // (if it's too early, don't change the frame yet)
    currFrame_ = (counter_ + 1) / frameRate_;
    
    if (loop) currFrame_ = currFrame_ % frames_;
    
    // Increment the counter
    counter_ = (counter_ + 1) % (frames_ * frameRate_);
}

void CAnimator::setSpriteClip(int index) {
    currClip_ = index;
    frames_ = static_cast<int>(spriteClips_[currClip_].size());
    
    counter_ = 0;
    currFrame_ = 0;
}
