//
//  Components.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-02-01.
//

#ifndef Components_hpp
#define Components_hpp

#include <stdio.h>
#include "Game.hpp"

typedef std::vector<int> Vec3Int;

// A base Component interface for all the components to inherit from
class Component {
public:
    virtual ~Component() = default; // Use the default implementation for the destructor
};

class CTransform : public Component {
public:
    Vec3Int position;
    Vec3Int rotation;
    Vec3Int scale;
};

class CSpriteRenderer : public Component {
public:
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};

class CBoxCollider : public Component {
public:
    SDL_Rect collider;
};

class CControls : public Component {
    // Empty for later
};

class CAnimator : public Component {
    // Empty for later
};

#endif /* Components_hpp */
