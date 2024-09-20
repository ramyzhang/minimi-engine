//
//  Entity.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-01-31.
//

#include "Entity.hpp"

Entity::Entity(const size_t id, const std::string& tag) {
    id_ = id;
    tag_ = tag;
}

std::string Entity::getTag() {
    return tag_;
}

bool Entity::isActive() {
    return active_;
}

void Entity::destroy() {
    active_ = false;
}
