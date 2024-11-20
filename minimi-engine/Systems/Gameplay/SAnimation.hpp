//
//  SAnimation.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-19.
//

#ifndef SAnimation_hpp
#define SAnimation_hpp

#include <stdio.h>
#include "CAnimator.hpp"
#include "Observer.hpp"

enum NPCAnim {
    ANGRY,
    LOVE
};

enum BowAnim {
    STATIC,
    SHOOTING
};

class SAnimation : public Observer {
public:
    void update();
};

#endif /* SAnimation_hpp */
