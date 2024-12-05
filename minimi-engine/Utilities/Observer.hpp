//
//  SObserver.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-19.
//

#ifndef Observer_hpp
#define Observer_hpp

#include <stdio.h>
#include "Event.h"
#include "Entity.hpp"

const int MAX_OBSERVERS = 20;

/** Subscribe to a subject to watch for notifications. */
class Observer {
public:
    virtual ~Observer() {}
    virtual void onNotify(Event event, std::shared_ptr<Entity> entity) = 0;
};

#endif /* SObserver_hpp */
