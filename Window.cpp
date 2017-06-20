//
// Created by douglas on 6/3/17.
//

#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "Window.h"

void Window::putPixel(double x, double y, bool isSelected, int color) {
    switch (color){
        case 1:
            glColor3f(1,0,0);
            break;
        default:
            glColor3f(0,0,0);
            break;
    }
    glPointSize(isSelected ? 2 : 1);
    glBegin(GL_POINTS);
    glVertex2f((GLfloat) x, (GLfloat) y);
    glEnd();
}

void Window::createLine(double x1, double y1, double x2, double y2, bool isSelected, int color) {
    double x = 0, y = 0;
    double dx = x2 - x1, dy = y2 - y1;
    double xmax = fmax(x1, x2), ymax = fmax(y1, y2);
    double xmin = fmin(x1, x2), ymin = fmin(y1, y2);

    if (dx == 0) {
        x = x1;
        for (y = ymin; y < ymax; y++) {
            putPixel(x, y, isSelected, color);
        }
        return;
    }
    if (dy == 0) {
        y = y1;
        for (x = xmin; x < xmax; x++) {
            putPixel(x, y, isSelected, color);
        }
        return;
    }

    double m = (float) dy / dx;
    double b = y1 - (m * x1);

    if (abs(dx) >= abs(dy)) {
        for (x = xmin; x < xmax; x++) {
            y = m * x + b;
            putPixel(x, y, isSelected, color);
        }
        return;
    } else if (abs(dx) < abs(dy)) {
        for (y = ymin; y < ymax; y++) {
            x = (y - b) / m;
            putPixel(x, y, isSelected, color);
        }
        return;
    } else {
        return;
    }
}
