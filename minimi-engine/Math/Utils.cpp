//
//  Utils.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-10.
//

#include "Utils.hpp"

bool incrementRate(int& counter_, int rate_) {
    // Tell the caller whether or not they should do something
    // Based on the desired rate
    
    counter_ = (counter_ + 1) % rate_;
    
    if (counter_ == 0) {
        return true;
    }
    
    return false;
}
