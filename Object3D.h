//
// Created by douglas on 6/3/17.
//

#include <string>

#ifndef INTERACTIVEOBJECT_OBJECT3D_H
#define INTERACTIVEOBJECT_OBJECT3D_H

using namespace std;

class Object3D {
public:
    string name;
    bool isSelected;
    int color;
    double **points; //Coordenadas x, y, z de cada ponto
    int **lines; //Indice do primeiro e ultimo ponto da linha
    int* trans; // Coordenadas x, y e z para projecao no sist de referencia do universo
    int* ang; //Angulos de rotacao nas coordenadas x, y e z
    float* scale; //Escala do objeto, x, y e z
    int p, l; //qnt de pontos e linhas
//    ~Object3D();
    Object3D(int,int);
    void makeCube();
    void printObjectInfo();
    void copyObject(Object3D *copy);
    void matrixMult (double (*mtr)[4]);
    void rotateX(double angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void scaleX(double scale);
    void scaleY(double scale);
    void scaleZ(double scale);
    void transX(double trans);
    void transY(double trans);
    void transZ(double trans);
    void scaleObject(float scale);
    void moveCenter(double center);
    void cavaleira_proj ();
    void cabinet_proj ();
    void orto_proj ();
    void persp1_proj ();
    void persp2_proj ();
    void showLinesCube ();
    void addTransY(int i);
    void addTransX(int i);
    void addTransZ(int i);
};

#endif //INTERACTIVEOBJECT_OBJECT3D_H
