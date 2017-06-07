//
// Created by douglas on 6/3/17.
//

#ifndef INTERACTIONLEAPMOTION_PRIMITIVES_H
#define INTERACTIONLEAPMOTION_PRIMITIVES_H


class Window {
    int width;
    int height;
public:
    Window (int height,int width);
    static void putPixel(double x, double y);
    static void createLine(double x1, double y1, double x2, double y2) ;
};


#endif //INTERACTIONLEAPMOTION_PRIMITIVES_H
