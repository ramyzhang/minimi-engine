//
//  EntityManager.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-29.
//

#include "EntityManager.hpp"

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {
    std::vector<char *> textureSheet;
    std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(totalEntities_, tag, textureSheet, 0, 0);
    
    entitiesToAdd_.push_back(newEntity);
    totalEntities_++;
    
    return newEntity;
}

EntityVector& EntityManager::getEntities() {
    return entities_;
}

EntityVector& EntityManager::getEntities(const std::string& tag) {
    return entityMap_[tag];
}

/** Perform iterator invalidation checks. */
void EntityManager::entityUpdate() {
    // Formally add entities that were added during this->addEntity()
    for (auto entity : entitiesToAdd_) {
        entities_.push_back(entity);
        entityMap_[entity->getTag()].push_back(entity);
    }
    
    // Erase entities from the entities vector if they're inactive
    entities_.erase(std::remove_if(entities_.begin(), entities_.end(), [] (std::shared_ptr<Entity> entity) { return !entity->isActive(); } ));
    
    // Clear the waiting room for new entities
    entitiesToAdd_.clear();
}

