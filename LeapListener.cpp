//
// Created by douglas on 6/8/17.
//

#include "LeapListener.h"
#include "Op.h"
#include "main.h"
#include <bits/stdc++.h>

using namespace std;

extern int funcProj;
extern Op current_option;
extern list<Object3D>::iterator current_object;
extern list<string>::iterator current_menu_option;
extern int64_t last_gesture_time;
extern bool isSubMenu;
extern list<string>::iterator current_submenu_option;

int PT = 2;
int PR = 50;

void LeapListener::onConnect(const Controller &controller) {
    cout << "Connected to LeapMotion" << std::endl;
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void LeapListener::onFrame(const Controller &controller) {
    const Leap::Frame frame = controller.frame();
    Leap::Frame previous = controller.frame(1);
    Leap::GestureList gestures = frame.gestures();
    if (!gestures.isEmpty()) {
        // Evita vários gestos de uma vez, verificando somente depois de 1 segundo
        if (frame.timestamp() > last_gesture_time + 1000000) {
            last_gesture_time = frame.timestamp();
            SwipeGesture swipeGesture = gestures[0];
            switch (gestures[0].type()) {
                case Gesture::TYPE_SWIPE:
                    switch (current_option) {
                        case Op::OPTION_MENU:
                            if (isSubMenu) {
                                if (swipeGesture.direction().x > 0.0)
                                    current_submenu_option++;
                                else
                                    current_submenu_option--;
                            } else {
                                if (swipeGesture.direction().x > 0.0)
                                    current_menu_option++;
                                else
                                    current_menu_option--;
                            }
                            break;
                        case Op::OPTION_SELECTION:
                            current_object->isSelected = false;
                            current_object++;
                        default:
                            break;
                    }
                    break;
                case Gesture::TYPE_KEY_TAP:
                    if (current_option == Op::OPTION_MENU) {
                        if (isSubMenu){
                            if (*current_submenu_option == "Cavaleira") {
                                funcProj = MENU_CAVALEIRA;
                            } else if (*current_submenu_option == "Cabinet") {
                                funcProj = MENU_CABINET;
                            } else if (*current_submenu_option == "Ponto de fuga X") {
                                funcProj = MENU_PERSP1;
                            } else if (*current_submenu_option == "Ponto de fuga X e Y") {
                                funcProj = MENU_PERSP2;
                            } else if (*current_submenu_option == "Voltar") {
                                isSubMenu = false;
                            }
                        }else {
                            if (*current_menu_option == "Projecoes") {
                                isSubMenu = true;
                            } else if (*current_menu_option == "Mostrar inf.") {

                            } else if (*current_menu_option == "Limpar") {
                                setup();
                            } else if (*current_menu_option == "Fechar Programa") {
                                exit(0);
                            } else if (*current_menu_option == "Sair do menu") {
                                current_option = static_cast<Op>((((int) current_option) + 1) % 5);
                            }
                        }
                    } else
                        current_option = static_cast<Op>((((int) current_option) + 1) % 5);
                    break;
                case Gesture::TYPE_INVALID:
                    break;
                case Gesture::TYPE_CIRCLE:
                    break;
                case Gesture::TYPE_SCREEN_TAP:
                    break;
            }
        }
    }

    Leap::HandList handsInFrame = frame.hands();
    if (!handsInFrame.isEmpty()) {
        Leap::Hand hand = handsInFrame.rightmost();
        cout << hand.fingers().count() << endl;
        switch (current_option) {
            case Op::OPTION_TRAN: {
                Leap::Vector linearMovement = hand.translation(previous);
                linearMovement *= PT;
                current_object->addTransX((int) linearMovement.x);
                current_object->addTransY((int) linearMovement.y);
                current_object->addTransZ((int) linearMovement.z);
                break;
            }
            case Op::OPTION_ROT: {
                float rotationAroundXAxis = frame.rotationAngle(previous, Vector::xAxis());
                current_object->rotateX(rotationAroundXAxis * PR);
                float rotationAroundYAxis = frame.rotationAngle(previous, Vector::yAxis());
                current_object->rotateY(rotationAroundYAxis * PR);
                float rotationAroundZAxis = frame.rotationAngle(previous, Vector::zAxis());
                current_object->rotateZ(rotationAroundZAxis * PR);
                break;
            }
            case Op::OPTION_SCA: {
                float zoomMotion = hand.scaleFactor(previous);
                current_object->scaleX(zoomMotion);
                current_object->scaleY(zoomMotion);
                current_object->scaleZ(zoomMotion);
                break;
            }
            default:
                break;
        }
    }
}