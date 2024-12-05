//
//  SSubject.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-19.
//

#ifndef Subject_hpp
#define Subject_hpp

#include <stdio.h>
#include "Observer.hpp"
#include "Entity.hpp"
#include "Event.h"

/** Send notifications to observers. */
class Subject {
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    
private:
    Observer* observers_[MAX_OBSERVERS];
    int numObservers_;

protected:
    void notify(Event event, std::shared_ptr<Entity> entity);
};

#endif /* SSubject_hpp */
