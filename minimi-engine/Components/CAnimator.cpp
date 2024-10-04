//
//  CAnimator.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-04.
//

#include "CAnimator.hpp"

void CAnimator::incrementFrame() {
    // Increment current frame based on framerate
    // (if it's too early, don't change the frame yet)
    currFrame_ = (counter_ + 1) / frameRate_;
    currFrame_ = currFrame_ % frames_;
    
    // Increment the counter
    counter_ = (counter_ + 1) % (frames_ * frameRate_);
}
