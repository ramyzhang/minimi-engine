//
//  CText.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-11-21.
//

#ifndef CText_hpp
#define CText_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Component.hpp"

class CText : public Component {
public:
    CText(char* t) : text(t) {};
    
    SDL_Texture* mTexture;
    
    char* text;
};

#endif /* CText_hpp */
