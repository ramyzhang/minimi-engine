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
#include "EntityManager.hpp"

class SAnimation : public Observer {
public:
    SAnimation(EntityManager* em) : em_(em) {};
    
    void update();
    
    virtual void onNotify(Event event, std::shared_ptr<Entity> entity) {
        switch (event) {
            case ENEMY_DIED: npcStateMachine(event, entity); break;
            case ARROW_SHOT: bowStateMachine(event); break;
            case PLAYER_HIT: break;
            case PLAYER_DIED: break;
            case NPC_LOVE: npcStateMachine(event, entity); break;
            default: break;
        }
    }
    
private:
    void npcStateMachine(Event event, std::shared_ptr<Entity> entity);
    void bowStateMachine(Event event);
    EntityManager* em_;
};

#endif /* SAnimation_hpp */
