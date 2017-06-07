//
// Created by douglas on 6/3/17.
//

#include <GL/glut.h>
#include <math.h>
#include "Window.h"

Window::Window(int height, int width) {
    this->width = width;
    this->height = height;
}

void Window::putPixel(double x, double y) {
    glPointSize(1.5);
    glBegin(GL_POINTS);
    glVertex2f((GLfloat) round(x), (GLfloat) round(y));
    glEnd();
}

void Window::createLine(double x1, double y1, double x2, double y2) {
    double x = 0, y = 0;
    double dx = x2 - x1, dy = y2 - y1;
    double xmax = fmax(x1, x2), ymax = fmax(y1, y2);
    double xmin = fmin(x1, x2), ymin = fmin(y1, y2);

    if (dx == 0) {
        x = x1;
        for (y = ymin; y < ymax; y++) {
            putPixel(x, y);
        }
        return;
    }
    if (dy == 0) {
        y = y1;
        for (x = xmin; x < xmax; x++) {
            putPixel(x, y);
        }
        return;
    }

    double m = (float) dy / dx;
    double b = y1 - (m * x1);

    if (abs(dx) >= abs(dy)) {
        for (x = xmin; x < xmax; x++) {
            y = m * x + b;
            putPixel(x, y);
        }
        return;
    } else if (abs(dx) < abs(dy)) {
        for (y = ymin; y < ymax; y++) {
            x = (y - b) / m;
            putPixel(x, y);
        }
        return;
    } else {
        return;
    }
}
