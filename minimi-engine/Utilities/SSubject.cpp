//
//  SSubject.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-19.
//

#include "SSubject.hpp"

void SSubject::addObserver(SObserver* observer) {
    if (numObservers_ >= MAX_OBSERVERS) return;
    observers_[numObservers_] = observer;
    numObservers_++;
}

void SSubject::removeObserver(SObserver* observer) {
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


void SSubject::notify(Event e) {
  for (int i = 0; i < numObservers_; i++) {
    observers_[i]->onNotify(e);
  }
}
