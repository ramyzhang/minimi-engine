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

const int MAX_OBSERVERS = 20;

/** Subscribe to a subject to watch for notifications. */
class Observer {
public:
  virtual ~Observer() {}
  virtual void onNotify(Event event) = 0;
};

#endif /* SObserver_hpp */
