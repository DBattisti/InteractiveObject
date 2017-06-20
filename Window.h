//
// Created by douglas on 6/3/17.
//

#ifndef INTERACTIVEOBJECT_PRIMITIVES_H
#define INTERACTIVEOBJECT_PRIMITIVES_H


class Window {
public:
    static void putPixel(double x, double y, bool isSelected, int color);
    static void createLine(double x1, double y1, double x2, double y2, bool isSelected, int color);
};


#endif //INTERACTIVEOBJECT_PRIMITIVES_H
