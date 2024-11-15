//
//  SSubject.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-19.
//

#ifndef SSubject_hpp
#define SSubject_hpp

#include <stdio.h>
#include "SObserver.hpp"

/** Send notifications to observers. */
class SSubject {
public:
    void addObserver(SObserver* observer);
    void removeObserver(SObserver* observer);
    
private:
    SObserver* observers_[MAX_OBSERVERS];
    int numObservers_;

protected:
    void notify(Event event);
};

#endif /* SSubject_hpp */
