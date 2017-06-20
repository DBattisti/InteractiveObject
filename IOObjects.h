//
// Created by douglas on 6/7/17.
//

#ifndef INTERACTIVEOBJECT_IOOBJECTS_H
#define INTERACTIVEOBJECT_IOOBJECTS_H


#include <list>
#include "Object3D.h"

class IOObjects {
public:
    static void store(list <Object3D>& objectsSelected);
    static void read(std::list<Object3D>&);
};


#endif //INTERACTIVEOBJECT_IOOBJECTS_H
