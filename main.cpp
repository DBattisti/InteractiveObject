#include <GL/glut.h>
#include <iostream>
#include <list>
#include <algorithm>
#include "Object3D.h"
#include "LeapListener.h"
#include "IOObjects.h"
#include "Op.h"
#include "main.h"

#define ANGLE_SPEED 5
#define SCALE_SPEED 1.1
#define TRANS_SPEED 5
#define WIDTH 800
#define HEIGHT 600

using namespace std;


Op current_option;

list<Object3D>::iterator current_object;
list<string>::iterator current_menu_option;
list<string>::iterator current_submenu_option;

int64_t last_gesture_time;
bool isSubMenu;
int funcProj;

std::list<Object3D> objects;
list<string> listMenu, listSubMenu;
void initListMenu();

void setup() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

    IOObjects::read(objects);
    current_object = objects.begin();

    initListMenu ();
    current_menu_option = listMenu.begin();
    current_submenu_option = listSubMenu.begin();

    last_gesture_time = 0;
    isSubMenu = false;
    current_option = Op::OPTION_MENU;
    funcProj = MENU_CAVALEIRA;
}

void initListMenu() {
    listMenu.clear();
    listMenu.push_back("Projecoes");
    listMenu.push_back("Mostrar inf.");
    listMenu.push_back("Limpar");
    listMenu.push_back("Sair do menu");
    listMenu.push_back("Fechar Programa");

    listSubMenu.clear();
    listSubMenu.push_back("Cavaleira");
    listSubMenu.push_back("Cabinet");
    listSubMenu.push_back("Ponto de fuga X");
    listSubMenu.push_back("Ponto de fuga X e Y");
    listSubMenu.push_back("Voltar");
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

    if (current_object == objects.end())
        current_object = objects.begin();
    if (current_menu_option == listMenu.end())
        current_menu_option = listMenu.begin();
    if (current_submenu_option == listSubMenu.end())
        current_submenu_option = listSubMenu.begin();

    current_object->isSelected = true;

    for (list<Object3D>::iterator it = objects.begin(); it != objects.end(); it++)
        proj(*it);

    std::string s;
    int count = 100;
    switch (current_option) {
        case Op::OPTION_TRAN:
            s = "TRANSLACAO";
            break;
        case Op::OPTION_ROT:
            s = "ROTACAO";
            break;
        case Op::OPTION_SCA:
            s = "ESCALA";
            break;
        case Op::OPTION_SELECTION:
            s = "SELECIONE";
            break;
        case Op::OPTION_MENU:
            s = "MENU";
            for (list<string>::iterator it = listMenu.begin(); it!=listMenu.end(); it++) {
                if (*it == *current_menu_option) {
                    printText(*it, 650, count -= 15, 1);
                }else{
                    printText(*it, 650, count -= 15, 0);
                }
            }
            break;
    }
    printText(s,10,10,0);

    if (isSubMenu){
        count = 100;
        for (list<string>::iterator it = listSubMenu.begin(); it!=listSubMenu.end(); it++) {
            if (*it == *current_submenu_option) {
                printText(*it, 450, count -= 15, 1);
            }else{
                printText(*it, 450, count -= 15, 0);
            }
        }
    }


    glutSwapBuffers();
}

void projChoose(int item_proj) {
    funcProj = item_proj;
    glutPostRedisplay();
}

void idle(void) {
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Transformacoes de objetos 3D usando Leap Motion");

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