//
// Created by douglas on 6/3/17.
//

#ifndef INTERACTIONLEAPMOTION_PRIMITIVES_H
#define INTERACTIONLEAPMOTION_PRIMITIVES_H


class Window {
    int width;
    int height;
    int **points_mtr;
    static float mtr_colors[5][3];
public:
    Window (int height,int width);
    static void putPixel(double x, double y);
//    void putPixelMtr (int x, int y, int idColor);
    static void createLine(double x1, double y1, double x2, double y2, int idColor) ;
//    void createLineMtr(float x1, float y1, float x2, float y2, int idColor);
//    void printMtrDisplay ();
//    void clearMtrDisplay ();
//    void delay ();
//    void boundaryFill (int xc, int yc, int idColor);
};


#endif //INTERACTIONLEAPMOTION_PRIMITIVES_H
