//
// Created by douglas on 6/8/17.
//

#ifndef INTERACTIVEOBJECT_LEAPLISTENER_H
#define INTERACTIVEOBJECT_LEAPLISTENER_H


#include <iostream>
#include <Leap.h>
#include "Object3D.h"

using namespace Leap;

class LeapListener : public Listener {
public:
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&);
};


#endif //INTERACTIVEOBJECT_LEAPLISTENER_H
