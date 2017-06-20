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

//Object3D::~Object3D(){
//    for (int i = 0; i < p; ++i)
//        delete[] points[i];
//    delete[] points;
//
//    for (int i = 0; i < l; ++i)
//        delete[] lines[i];
//    delete[] lines;
//
//    delete[] scale;
//    delete[] ang;
//    delete[] trans;
//}

Object3D::Object3D(int n_points, int m_lines) {
    p = n_points;
    l = m_lines;

    // Init arrays de informações
    scale = new float[3];
    std::fill(&scale[0],&scale[3],0);
    ang = new int[3];
    std::fill(&ang[0],&ang[3],0);
    trans = new int[3];
    std::fill(&trans[0],&trans[3],0);

    // Init Matriz de pontos
    points = new double *[n_points];
    for (int i = 0; i < n_points; i++)
        points[i] = new double[qnt_coord];

    // Init Matriz de linhas
    lines = new int *[m_lines];
    for (int i = 0; i < m_lines; i++)
        lines[i] = new int[qnt_points];

};

void Object3D::copyObject(Object3D *copy) {
    copy->color = color;
    copy->isSelected = isSelected;
    for (size_t j = 0; j < copy->p; j++) {
        for (size_t i = 0; i < qnt_coord; i++) {
            copy->points[j][i] = points[j][i];
        }
    }
    for (size_t j = 0; j < copy->l; j++) {
        for (size_t i = 0; i < qnt_points; i++) {
            copy->lines[j][i] = lines[j][i];
        }
    }
    for (int i = 0; i < 3; ++i) {
        copy->trans[i] = trans[i];
    }
    for (int i = 0; i < 3; ++i) {
        copy->ang[i] = ang[i];
    }
    for (int i = 0; i < 3; ++i) {
        copy->scale[i] = scale[i];
    }
}

void Object3D::printObjectInfo(){
    printf("\n##########################\n");
    printf("Quantidade de pontos: %d\n",p);
    printf("Quantidade de linhas: %d\n",l);
    printf("\nAngulos rotacionados em x, y e z:\n");
    for (int i = 0; i < 3; ++i)
        std::cout << ang[i] << " ";
    printf("\nValores transladados em x, y e z:\n");
    for (int i = 0; i < 3; ++i)
        std::cout << trans[i] << " ";
    printf("\nValores escalados em x, y e z:\n");
    for (int i = 0; i < 3; ++i)
        std::cout << scale[i] << " ";
    printf("\nMatriz de pontos:\n");
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < qnt_coord; ++j)
            std::cout << points[i][j] << " ";
        std::cout << "\n";
    }
    printf("\nMatriz de linhas:\n");
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < qnt_points; ++j)
            std::cout << lines[i][j] << " ";
        std::cout << "\n";
    }
}

void Object3D::makeCube() {
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

void Object3D::matrixMult(double (*mtr)[4]) {
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

void Object3D::rotateX(double angle) {
    ang[0] += angle;
    double rotateMtr[4][4] = {1, 0, 0, 0,
                              0, cos(angle * GTOR), sin(angle * GTOR), 0,
                              0, sin(angle * GTOR) * -1, cos(angle * GTOR), 0,
                              0, 0, 0, 1};
    matrixMult(rotateMtr);
}

void Object3D::rotateY(float angle) {
    ang[1] += angle;
    double rotateMtr[4][4] = {cos(angle * GTOR), 0, sin(angle * GTOR) * -1, 0,
                              0, 1, 0, 0,
                              sin(angle * GTOR), 0, cos(angle * GTOR), 0,
                              0, 0, 0, 1};
    matrixMult(rotateMtr);
}

void Object3D::rotateZ(float angle) {
    ang[2] += angle;
    double rotateMtr[4][4] = {cos(angle * GTOR), sin(angle * GTOR), 0, 0,
                              sin(angle * GTOR) * -1, cos(angle * GTOR), 0, 0,
                              0, 0, 1, 0,
                              0, 0, 0, 1};
    matrixMult(rotateMtr);
}

void Object3D::scaleX(double scale) {
    this->scale[0] += scale;
    double scaleMtr[4][4] = {scale, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1};
    matrixMult(scaleMtr);
}

void Object3D::scaleY(double scale) {
    this->scale[1] += scale;
    double scaleMtr[4][4] = {1, 0, 0, 0,
                             0, scale, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1};
    matrixMult(scaleMtr);
}

void Object3D::scaleZ(double scale) {
    this->scale[2] += scale;
    double scaleMtr[4][4] = {1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, scale, 0,
                             0, 0, 0, 1};
    matrixMult(scaleMtr);
}

void Object3D::addTransX(int i) {
    this->trans[0] += i;
}

void Object3D::addTransY(int i) {
    this->trans[1] += i;
}

void Object3D::addTransZ(int i) {
    this->trans[2] += i;
}

void Object3D::transX(int trans) {
    trans += this->trans[0];
    double transMtr[4][4] = {1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             trans, 0, 0, 1};
    matrixMult(transMtr);
}

void Object3D::transY(int trans) {
    trans += this->trans[1];
    double transMtr[4][4] = {1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, trans, 0, 1};
    matrixMult(transMtr);
}

void Object3D::transZ(int trans) {
    trans += this->trans[2];
    double transMtr[4][4] = {1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, trans, 1};
    matrixMult(transMtr);
}

void Object3D::scaleObject(float scale){
    scaleX(scale);
    scaleY(scale);
    scaleZ(scale);
}

void Object3D::moveCenter(int center){
    transX(center);
    transY(center);
}

void Object3D::cavaleira_proj() {
    float alfa = 0.707;
    double cavMtr[4][4] = {1, 0, 0, 0,
                           0, 1, 0, 0,
                           alfa, alfa, 0, 0,
                           0, 0, 0, 1};
    matrixMult(cavMtr);
}

void Object3D::cabinet_proj() {
    double alfa = 0.707 / 2;
    double cabMtr[4][4] = {1, 0, 0, 0,
                           0, 1, 0, 0,
                           alfa, alfa, 0, 0,
                           0, 0, 0, 1};
    matrixMult(cabMtr);
}

void Object3D::orto_proj() {
    double ortoMtr[4][4] = {1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 1};
    matrixMult(ortoMtr);
}

void Object3D::persp1_proj() {
    double fz = -100.0;
    double perspMtr[4][4] = {1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, -1 / fz,
                             0, 0, 0, 1};
    matrixMult(perspMtr);
}

void Object3D::persp2_proj() {
    double fz = -100.0;
    double fx = -100.0;
    double perspMtr[4][4] = {1, 0, 0, -1 / fx,
                             0, 1, 0, 0,
                             0, 0, 1, -1 / fz,
                             0, 0, 0, 1};
    matrixMult(perspMtr);
}

void Object3D::showLinesCube(){
    double x1, y1, x2, y2;
    for (size_t j = 0; j < l; j++) {
        x1 = (points[ lines[j][0] ][0])/points[ lines[j][0] ][3];
        y1 = (points[ lines[j][0] ][1])/points[ lines[j][0] ][3];
        x2 = (points[ lines[j][1] ][0])/points[ lines[j][1] ][3];
        y2 = (points[ lines[j][1] ][1])/points[ lines[j][1] ][3];
        Window::createLine(x1, y1, x2, y2, isSelected, color);
    }
}





