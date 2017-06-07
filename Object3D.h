//
// Created by douglas on 6/3/17.
//

#ifndef INTERACTIONLEAPMOTION_OBJECT3D_H
#define INTERACTIONLEAPMOTION_OBJECT3D_H


class Object3D {
    double **points; //Coordenadas x, y, z de cada ponto
    int **lines; //Indice do primeiro e ultimo ponto da linha
    int* trans; // Coordenadas x, y e z para projecao no sist de referencia do universo
    int* ang; //Angulos de rotacao nas coordenadas x, y e z
    float* scale; //Escala do objeto, x, y e z
    int p, l; //qnt de pontos e linhas
public:
    Object3D();
    Object3D(int,int);
    void cleanObject();
    void makeCube();
    void printObjectInfo();
    Object3D copyObject ();
    void matrixMult (double (*mtr)[4]);
    void rotateX( float angle);
    void rotateY( float angle);
    void rotateZ( float angle);
    void scaleX(double scale);
    void scaleY(double scale);
    void scaleZ(double scale);
    void transX(int trans);
    void transY(int trans);
    void transZ(int trans);
    void scaleObject(float scale);
    void moveCenter(int center);
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

#endif //INTERACTIONLEAPMOTION_OBJECT3D_H
