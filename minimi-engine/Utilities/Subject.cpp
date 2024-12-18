//
//  SSubject.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-19.
//

#include "Subject.hpp"

void Subject::addObserver(Observer* observer) {
    if (numObservers_ >= MAX_OBSERVERS) return;
    observers_[numObservers_] = observer;
    numObservers_++;
}

void Subject::removeObserver(Observer* observer) {
    if (numObservers_ <= 0) return;
    
    // Iterate through the list to find the observer and remove it
    int index = 0;
    bool found = false;
    while (index < numObservers_) {
        if (found) observers_[index - 1] = observers_[index];
        
        if (observers_[index] == observer) {
            found = true;
            observers_[index] = NULL;
        }
    }
    
    if (!found) {
        printf("Couldn't find observer.\n");
    } else {
        numObservers_--;
    }
}

void Subject::notify(Event e, std::shared_ptr<Entity> entity) {
    for (int i = 0; i < numObservers_; i++) {
      observers_[i]->onNotify(e, entity);
    }
}
