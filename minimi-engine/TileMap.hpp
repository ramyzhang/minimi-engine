//
//  TileMap.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-23.
//

#ifndef TileMap_hpp
#define TileMap_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "SRenderer.hpp"

class TileMap {

public:
    TileMap();
    ~TileMap();
    
    TileMap(SRenderer* r) : renderer_(r) {};
    
    void loadMap(int newMap[20][25]);
    void renderMap();

private:
    SRenderer* renderer_;
    SDL_Rect srcRect_, destRect_;
    SDL_Texture *stone_;
    SDL_Texture *grass_;
    SDL_Texture *water_;
    
    int tileMap_[20][25];
};

#endif /* TileMap_hpp */
