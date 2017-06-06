//
// Created by douglas on 6/3/17.
//

#include <iostream>
#include <cmath>
#include "Object3D.h"
#include "Window.h"

#define qnt_coord 4
#define qnt_points 2
#define PI 3.14159265

double GTOR = PI / 180;

object3D::object3D(int n_points, int m_lines) {
    p = n_points;
    l = m_lines;

    // Init arrays de informações
    scale = new float[3];
    ang = new int[3];
    trans = new int[3];

    // Init Matriz de pontos
    points = new double *[n_points];
    for (int i = 0; i < n_points; i++) {
        points[i] = new double[qnt_coord];
    }

    // Init Matriz de linhas
    lines = new int *[m_lines];
    for (int i = 0; i < m_lines; i++) {
        lines[i] = new int[qnt_points];
    }
};

object3D object3D::copyObject() {
    object3D copy(p,l);
    for (size_t j = 0; j < copy.p; j++) {
        for (size_t i = 0; i < qnt_coord; i++) {
            copy.points[j][i] = points[j][i];
        }
    }
    for (size_t j = 0; j < copy.l; j++) {
        for (size_t i = 0; i < qnt_points; i++) {
            copy.lines[j][i] = lines[j][i];
        }
    }
    return copy;
}

void object3D::cleanObject() {
    for (int i = 0; i < p; ++i)
        delete[] points[i];
    delete[] points;

    for (int i = 0; i < l; ++i)
        delete[] lines[i];
    delete[] lines;

    delete[] scale;
    delete[] ang;
    delete[] trans;
}

void object3D::printObjectInfo(){
    printf("\n##########################\n");
    printf("Quantidade de pontos: %d\n",p);
    printf("Quantidade de linhas: %d\n",l);
    printf("Angulos rotacionados em x, y e z:\n");
    for (int i = 0; i < 3; ++i)
        std::cout << ang[i];
    printf("Valores transladados em x, y e z:\n");
    for (int i = 0; i < 3; ++i)
        std::cout << trans[i];
    printf("Valores escalados em x, y e z:\n");
    for (int i = 0; i < 3; ++i)
        std::cout << scale[i];
    printf("Matriz de pontos:\n");
    for (int i = 0; i < p*qnt_coord; i++)
        std::cout << points[i];
    printf("Matriz de linhas:\n");
    for (int i = 0; i < l*qnt_points; i++)
        std::cout << lines[i];
}

void object3D::makeCube() {
    points[0][0] =  1.0; points[0][1] =  1.0; points[0][2] =  1.0; points[0][3] = 1.0;//p3
    points[1][0] =  1.0; points[1][1] =  1.0; points[1][2] = -1.0; points[1][3] = 1.0;//p6
    points[2][0] =  1.0; points[2][1] = -1.0; points[2][2] =  1.0; points[2][3] = 1.0;//p2
    points[3][0] =  1.0; points[3][1] = -1.0; points[3][2] = -1.0; points[3][3] = 1.0;//p7
    points[4][0] = -1.0; points[4][1] =  1.0; points[4][2] =  1.0; points[4][3] = 1.0;//p4
    points[5][0] = -1.0; points[5][1] =  1.0; points[5][2] = -1.0; points[5][3] = 1.0;//p5
    points[6][0] = -1.0; points[6][1] = -1.0; points[6][2] =  1.0; points[6][3] = 1.0;//p1
    points[7][0] = -1.0; points[7][1] = -1.0; points[7][2] = -1.0; points[7][3] = 1.0;//p8

    //face frente
    lines [0][0] = 6; lines [0][1] = 2;
    lines [1][0] = 2; lines [1][1] = 0;
    lines [2][0] = 0; lines [2][1] = 4;
    lines [3][0] = 4; lines [3][1] = 6;
    //face tras
    lines [4][0] = 5; lines [4][1] = 1;
    lines [5][0] = 1; lines [5][1] = 3;
    lines [6][0] = 3; lines [6][1] = 7;
    lines [7][0] = 7; lines [7][1] = 5;
    //interligações
    lines [8][0] = 4; lines [8][1] = 5;
    lines [9][0] = 0; lines [9][1] = 1;
    lines[10][0] = 2; lines[10][1] = 3;
    lines[11][0] = 6; lines[11][1] = 7;
}

void object3D::matrixMult(double (*mtr)[4]) {
    double x, y, z, m;
    for (size_t i = 0; i < p; i++) {
        x = points[i][0];
        y = points[i][1];
        z = points[i][2];
        m = points[i][3];
        points[i][0] = x * mtr[0][0] + y * mtr[1][0] + z * mtr[2][0] + m * mtr[3][0];
        points[i][1] = x * mtr[0][1] + y * mtr[1][1] + z * mtr[2][1] + m * mtr[3][1];
        points[i][2] = x * mtr[0][2] + y * mtr[1][2] + z * mtr[2][2] + m * mtr[3][2];
        points[i][3] = x * mtr[0][3] + y * mtr[1][3] + z * mtr[2][3] + m * mtr[3][3];
    }
}

void object3D::rotateX(float angle) {
    ang[0] += angle;
    double rotateMtr[4][4] = {1, 0, 0, 0,
                              0, cos(angle * GTOR), sin(angle * GTOR), 0,
                              0, sin(angle * GTOR) * -1, cos(angle * GTOR), 0,
                              0, 0, 0, 1};
    matrixMult(rotateMtr);
}


void object3D::rotateY(float angle) {
    ang[1] += angle;
    double rotateMtr[4][4] = {cos(angle * GTOR), 0, sin(angle * GTOR) * -1, 0,
                              0, 1, 0, 0,
                              sin(angle * GTOR), 0, cos(angle * GTOR), 0,
                              0, 0, 0, 1};
    matrixMult(rotateMtr);
}

void object3D::rotateZ(float angle) {
    ang[2] += angle;
    double rotateMtr[4][4] = {cos(angle * GTOR), sin(angle * GTOR), 0, 0,
                             sin(angle * GTOR) * -1, cos(angle * GTOR), 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1};
    matrixMult(rotateMtr);
}

void object3D::scaleX(float scale) {
    this->scale[0] += scale;
    double scaleMtr[4][4] = {scale, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1};
    matrixMult(scaleMtr);
}

void object3D::scaleY(float scale) {
    this->scale[1] += scale;
    double scaleMtr[4][4] = {1, 0, 0, 0,
                             0, scale, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1};
    matrixMult(scaleMtr);
}

void object3D::scaleZ(float scale) {
    this->scale[2] += scale;
    double scaleMtr[4][4] = {1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, scale, 0,
                             0, 0, 0, 1};
    matrixMult(scaleMtr);
}

void object3D::transX(int trans) {
    this->trans[0] += trans;
    double transMtr[4][4] = {1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             trans, 0, 0, 1};
    matrixMult(transMtr);
}

void object3D::transY(int trans) {
    this->trans[1] += trans;
    double transMtr[4][4] = {1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, trans, 0, 1};
    matrixMult(transMtr);
}

void object3D::transZ(int trans) {
    this->trans[2] += trans;
    double transMtr[4][4] = {1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, trans, 1};
    matrixMult(transMtr);
}

void object3D::scaleObject(float scale){
    scaleX(scale);
    scaleY(scale);
    scaleZ(scale);
}

void object3D::moveCenter(int center){
    transX(center);
    transY(center);
}

void object3D::cavaleira_proj() {
    float alfa = 0.707;
    double cavMtr[4][4] = {1, 0, 0, 0,
                          0, 1, 0, 0,
                          alfa, alfa, 0, 0,
                          0, 0, 0, 1};
    matrixMult(cavMtr);
}

void object3D::cabinet_proj() {
    double alfa = 0.707 / 2;
    double cabMtr[4][4] = {1, 0, 0, 0,
                          0, 1, 0, 0,
                          alfa, alfa, 0, 0,
                          0, 0, 0, 1};
    matrixMult(cabMtr);
}

void object3D::orto_proj() {
    double ortoMtr[4][4] = {1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 0, 0,
                           0, 0, 0, 1};
    matrixMult(ortoMtr);
}

void object3D::persp1_proj() {
    double fz = -100.0;
    double perspMtr[4][4] = {1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, -1 / fz,
                            0, 0, 0, 1};
    matrixMult(perspMtr);
}

void object3D::persp2_proj() {
    double fz = -100.0;
    double fx = -100.0;
    double perspMtr[4][4] = {1, 0, 0, -1 / fx,
                            0, 1, 0, 0,
                            0, 0, 1, -1 / fz,
                            0, 0, 0, 1};
    matrixMult(perspMtr);
}

void object3D::showLinesCube(){
    double x1, y1, x2, y2;
    int idColor = 1;
    for (size_t j = 0; j < l; j++) {
        x1 = (points[ lines[j][0] ][0])/points[ lines[j][0] ][3];
        y1 = (points[ lines[j][0] ][1])/points[ lines[j][0] ][3];
        x2 = (points[ lines[j][1] ][0])/points[ lines[j][1] ][3];
        y2 = (points[ lines[j][1] ][1])/points[ lines[j][1] ][3];
        Window::createLine(x1,y1,x2,y2,idColor);
    }
}



