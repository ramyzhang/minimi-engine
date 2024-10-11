//
//  EntityManager.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-29.
//

#include "EntityManager.hpp"

EntityManager::EntityManager() {
    totalEntities_ = 0;
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {
    if (totalEntities_ >= MAX_ENTITIES) {
        printf("Reached maximum number of entities.");
        return nullptr;
    }
    
    auto newEntity = std::shared_ptr<Entity>(new Entity(totalEntities_, tag));
    
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
    auto new_end = std::remove_if(entities_.begin(), entities_.end(), [] (std::shared_ptr<Entity> entity) { return !entity->isActive(); } );
        
    for (auto it = entityMap_.begin(); it != entityMap_.end(); ++it) {
        auto new_map_end = std::remove_if(it->second.begin(), it->second.end(), [] (std::shared_ptr<Entity> entity) { return !entity->isActive(); } );
        it->second.erase(new_map_end, it->second.end());
    }
    
    totalEntities_ = totalEntities_ - (std::distance(new_end, entities_.end()));
    entities_.erase(new_end, entities_.end());
    
    // Clear the waiting room for new entities
    entitiesToAdd_.clear();
}

