#include <GL/glut.h>
#include <iostream>
#include <list>
#include <algorithm>
#include "Object3D.h"
#include "LeapListener.h"
#include "IOObjects.h"

#define ANGLE_SPEED 5
#define SCALE_SPEED 1.1
#define TRANS_SPEED 5
#define WIDTH 800
#define HEIGHT 600

using namespace std;
enum MENU_TYPE {
    MENU_EXIT,
    MENU_CLEAN,
    MENU_PRINT,
    MENU_ORTO,
    MENU_CAVALEIRA,
    MENU_CABINET,
    MENU_PERSP1,
    MENU_PERSP2
};

int trans_type;
list<Object3D>::iterator selected;
list<string>::iterator listMenuSelected;

int funcProj;
int win, main_menu, proj_menu;
int current;

std::list<Object3D> objects;
list<string> listMenu, listSubMenu;
void initListMenu();

void setup() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

    IOObjects::read(objects);
    selected = objects.begin();

    initListMenu ();
    listMenuSelected = listMenu.begin();

    current = 0;
    trans_type = 3;
    funcProj = MENU_CAVALEIRA;
}

void initListMenu() {
    listMenu.push_back("Projecoes");
    listMenu.push_back("Mostrar inf.");
    listMenu.push_back("Limpar");
    listMenu.push_back("Sair");
    listMenu.push_back("Voltar");

    listSubMenu.push_back("Cavaleira");
    listSubMenu.push_back("Cabinet");
    listSubMenu.push_back("Ponto de fuga X");
    listSubMenu.push_back("Ponto de fuga X e Y");
}

void proj(Object3D &orig) {
    Object3D copy(orig.p, orig.l);
    orig.copyObject(&copy);
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
        default:
            break;
    }
    copy.moveCenter(250);
    copy.showLinesCube();
}

void printText (string s, int x, int y, int cor){
    switch (cor){
        case 0:
            glColor3f(0,0,0);
            break;
        case 1:
            glColor3f(1,0,0);
        default:
            break;
    }
    glRasterPos2i(x, y);
    void *font = GLUT_BITMAP_9_BY_15;
    for (std::string::iterator i = s.begin(); i != s.end(); ++i) {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    if (selected == objects.end())
        selected = objects.begin();
    if (listMenuSelected == listMenu.end())
        listMenuSelected = listMenu.begin();

    selected->isSelected = true;

    for (list<Object3D>::iterator it = objects.begin(); it != objects.end(); it++)
        proj(*it);

    std::string s;
    int count = 100;
    switch (trans_type) {
        case 0:
            s = "TRANSLACAO";
            break;
        case 1:
            s = "ROTACAO";
            break;
        case 2:
            s = "ESCALA";
            break;
        case 3:
            s = "SELECIONE";
            break;
        case 4:
            s = "MENU";
            for (list<string>::iterator it = listMenu.begin(); it!=listMenu.end(); it++) {
                if (*it == *listMenuSelected) {
                    printText(*it, 650, count -= 15, 1);
                }else{
                    printText(*it, 650, count -= 15, 0);
                }
            }
            break;
        default:
            s = "default";
    }
    printText(s,10,10,0);


    glutSwapBuffers();
}



void projChoose(int item_proj) {
    funcProj = item_proj;
    glutPostRedisplay();
}

void choose(int item_menu) {
    switch (item_menu) {
        case MENU_EXIT:
            glutDestroyWindow(win);
            break;
        case MENU_CLEAN:
            glutPostRedisplay();
            break;
        case MENU_PRINT:
            objects.front().printObjectInfo();
            break;
        default:
            printf("Invalid menu item:%d\n", item_menu);
    }
}

void transformations(unsigned char key, int x, int y) {
//    cout << x << " " << y << endl;
    switch (key) {
        case 'q':
            current++;
            current %= 5;
            // Rotacionar
        case 'z':
            objects.front().rotateX(ANGLE_SPEED);
            break;
        case 'x':
            objects.front().rotateY(ANGLE_SPEED);
            break;
        case 'c':
            objects.front().rotateZ(ANGLE_SPEED);
            break;
        case 'a':
            objects.front().rotateX(-ANGLE_SPEED);
            break;
        case 's':
            objects.front().rotateY(-ANGLE_SPEED);
            break;
        case 'd':
            objects.front().rotateZ(-ANGLE_SPEED);
            break;
            // Escalonar
        case 'f':
            objects.front().scaleX(SCALE_SPEED);
            break;
        case 'g':
            objects.front().scaleY(SCALE_SPEED);
            break;
        case 'h':
            objects.front().scaleZ(SCALE_SPEED);
            break;
        case 'v':
            objects.front().scaleX(1 / SCALE_SPEED);
            break;
        case 'b':
            objects.front().scaleY(1 / SCALE_SPEED);
            break;
        case 'n':
            objects.front().scaleZ(1 / SCALE_SPEED);
            break;
            // Transladar
        case '8':
            objects.front().addTransY(TRANS_SPEED);
            break;
        case '2':
            objects.front().addTransY(-TRANS_SPEED);
            break;
        case '4':
            objects.front().addTransX(-TRANS_SPEED);
            break;
        case '6':
            objects.front().addTransX(TRANS_SPEED);
            break;
        case '1':
            objects.front().addTransZ(TRANS_SPEED);
            break;
        case '3':
            objects.front().addTransZ(-TRANS_SPEED);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void idle(void) {
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);

    win = glutCreateWindow("Criacao de objetos 3D");

    proj_menu = glutCreateMenu(projChoose);
    glutAddMenuEntry("Paralela Ortografica Multiplas Vistas", MENU_ORTO);
    glutAddMenuEntry("Paralela Obliqua Cavaleira", MENU_CAVALEIRA);
    glutAddMenuEntry("Paralela Obliqua Cabinet", MENU_CABINET);
    glutAddMenuEntry("Perspectiva com um ponto de fuga em Z", MENU_PERSP1);
    glutAddMenuEntry("Perspectiva com dois pontos de fuga, em X e Z", MENU_PERSP2);

    main_menu = glutCreateMenu(choose);
    glutAddSubMenu("Projecoes", proj_menu);
    glutAddMenuEntry("Info", MENU_PRINT);
    glutAddMenuEntry("Refresh", MENU_CLEAN);
    glutAddMenuEntry("Sair", MENU_EXIT);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutKeyboardFunc(transformations);

    setup();
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    // Init LeapMotion
    Leap::Controller controller;
    LeapListener listener;
    controller.addListener(listener);

    glutMainLoop();

    controller.removeListener(listener);

    return 0;
}