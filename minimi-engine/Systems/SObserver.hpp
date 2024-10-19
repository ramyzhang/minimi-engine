//
//  SObserver.hpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-10-19.
//

#ifndef SObserver_hpp
#define SObserver_hpp

#include <stdio.h>

const int MAX_OBSERVERS = 20;

enum Event {
    ENEMY_DIED,
    ARROW_SHOT,
    PLAYER_HIT,
    PLAYER_DIED,
};

class SObserver {
public:
  virtual ~SObserver() {}
  virtual void onNotify(Event event) = 0;
};

#endif /* SObserver_hpp */
