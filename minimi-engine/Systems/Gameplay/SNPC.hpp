//
//  SNPC.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-12-05.
//

#ifndef SNPC_hpp
#define SNPC_hpp

#include <stdio.h>
#include <stdio.h>
#include "CNPC.hpp"
#include "Observer.hpp"
#include "EntityManager.hpp"

class SNPC : public Observer {

public:
    SNPC(EntityManager* em) : em_(em) {};
    
    virtual void onNotify(Event event, std::shared_ptr<Entity> entity) {
        switch (event) {
            case ENEMY_DIED: break;
            case ARROW_SHOT: break;
            case PLAYER_HIT: break;
            case PLAYER_DIED: break;
            case NPC_LOVE: findLoveTarget(entity); break;
            default: break;
        }
    }
    
    void init(std::shared_ptr<Entity> player);
    void update();
        
private:
    EntityManager* em_;
    std::shared_ptr<Entity> player_;
    
    void updateTargetPosition(std::shared_ptr<Entity> npc);
    void findLoveTarget(std::shared_ptr<Entity> npc);
};

#endif /* SNPC_hpp */
