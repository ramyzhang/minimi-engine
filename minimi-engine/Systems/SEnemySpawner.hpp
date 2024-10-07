//
//  SEnemySpawner.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-05.
//

#ifndef SEnemySpawner_hpp
#define SEnemySpawner_hpp

#include <stdio.h>
#include <math.h>
#include "EntityManager.hpp"
#include "TextureManager.hpp"
#include "Vec2.hpp"
#include "Game.hpp"

const float NPC_SPEED = 1;
const int SPAWN_RATE = 2;

void sSpawnEnemy(std::shared_ptr<Entity> player);
void sEnemyUpdate(std::shared_ptr<Entity> npc, std::shared_ptr<Entity> player);

#endif /* SEnemySpawner_hpp */
