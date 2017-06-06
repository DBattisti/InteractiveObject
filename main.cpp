#include <GL/glut.h>
#include <iostream>
#include "Object3D.h"
#include "Window.h"

#define ANGLE_SPEED 5
#define SCALE_SPEED 1.1
#define TRANS_SPEED 5
#define WIDTH 600
#define HEIGHT 600

enum MENU_TYPE{
    MENU_EXIT,
    MENU_CLEAN,
    MENU_PRINT,
    MENU_ORTO,
    MENU_CAVALEIRA,
    MENU_CABINET,
    MENU_PERSP1,
    MENU_PERSP2
};

int funcProj;
int win, main_menu, proj_menu;

object3D orig (8,12);
object3D copy (8,12);
Window pri (WIDTH,HEIGHT);

void setup(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(0, WIDTH-1, 0, HEIGHT-1);
    orig.makeCube();
    orig.scaleObject(50.0);
    funcProj = MENU_CAVALEIRA;
}

void proj (){
    copy = orig.copyObject();
    switch (funcProj) {
        case MENU_CAVALEIRA:
            copy.cavaleira_proj();
            break;
        case MENU_CABINET:
            copy.cabinet_proj();
            break;
        case MENU_ORTO:
            copy.orto_proj();
            break;
        case MENU_PERSP1:
            copy.transZ(50);
            copy.persp1_proj();
            break;
        case MENU_PERSP2:
            copy.transZ(50);
            copy.transX(50);
            copy.persp2_proj();
            break;
        default:break;
    }
    copy.moveCenter(250);
    copy.showLinesCube();
    copy.cleanObject();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    Window::createLine(300.0,0.0,300.0,600.0,2);
    Window::createLine(0.0,300.0,600.0,300.0,2);

    proj();
    glutSwapBuffers();
}

void projChoose (int item_proj){
    funcProj = item_proj;
    glutPostRedisplay();
}

void choose (int item_menu){
    switch (item_menu) {
        case MENU_EXIT:
            glutDestroyWindow(win);
            break;
        case MENU_CLEAN:
            glutPostRedisplay();
            break;
        case MENU_PRINT:
            orig.printObjectInfo();
            break;
        default:
            printf("Invalid menu item:%d\n", item_menu);
    }
}

void transformations (unsigned char key,int x, int y){
    switch (key) {
        // Rotacionar
        case 'z':
            orig.rotateX(ANGLE_SPEED);
            break;
        case 'x':
            orig.rotateY(ANGLE_SPEED);
            break;
        case 'c':
            orig.rotateZ(ANGLE_SPEED);
            break;
        case 'a':
            orig.rotateX(-ANGLE_SPEED);
            break;
        case 's':
            orig.rotateY(-ANGLE_SPEED);
            break;
        case 'd':
            orig.rotateZ(-ANGLE_SPEED);
            break;
            // Escalonar
        case 'f':
            orig.scaleX(SCALE_SPEED);
            break;
        case 'g':
            orig.scaleY(SCALE_SPEED);
            break;
        case 'h':
            orig.scaleZ(SCALE_SPEED);
            break;
        case 'v':
            orig.scaleX(1/SCALE_SPEED);
            break;
        case 'b':
            orig.scaleY(1/SCALE_SPEED);
            break;
        case 'n':
            orig.scaleZ(1/SCALE_SPEED);
            break;
            // Transladar
        case '8':
            orig.transY(TRANS_SPEED);
            break;
        case '2':
            orig.transY(-TRANS_SPEED);
            break;
        case '4':
            orig.transX(-TRANS_SPEED);
            break;
        case '6':
            orig.transX(TRANS_SPEED);
            break;
        case '1':
            orig.transZ(TRANS_SPEED);
            break;
        case '3':
            orig.transZ(-TRANS_SPEED);
            break;
    }
    glutPostRedisplay();
}

int main (int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(WIDTH,HEIGHT);

    win = glutCreateWindow("Criacao de objetos 3D");

    proj_menu = glutCreateMenu(projChoose);
    glutAddMenuEntry("Paralela Ortografica Multiplas Vistas",MENU_ORTO);
    glutAddMenuEntry("Paralela Obliqua Cavaleira",MENU_CAVALEIRA);
    glutAddMenuEntry("Paralela Obliqua Cabinet",MENU_CABINET);
    glutAddMenuEntry("Perspectiva com um ponto de fuga em Z",MENU_PERSP1);
    glutAddMenuEntry("Perspectiva com dois pontos de fuga, em X e Z",MENU_PERSP2);

    main_menu = glutCreateMenu(choose);
    glutAddSubMenu("Projecoes",proj_menu);
    glutAddMenuEntry("Info",MENU_PRINT);
    glutAddMenuEntry("Refresh",MENU_CLEAN);
    glutAddMenuEntry("Sair",MENU_EXIT);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutKeyboardFunc(transformations);

    setup();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}