//
// Created by douglas on 6/8/17.
//

#include "LeapListener.h"
#include <bits/stdc++.h>

using namespace std;

extern int trans_type;
extern list<Object3D>::iterator selected;
extern list<string>::iterator listMenuSelected;

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

    Leap::GestureList gestures = frame.gestures(previous);
    if (!gestures.isEmpty()) {
        for (int i = 0; i < gestures.count(); i++) {
            switch (gestures[i].type()) {
                case Gesture::TYPE_SWIPE:
                    switch (trans_type) {
                        case 4:
                            listMenuSelected++;
                            break;
                        case 3:
                            selected->isSelected = false;
                            selected++;
                        default:
                            break;
                    }
                    break;
                case Gesture::TYPE_KEY_TAP:
                    trans_type = (trans_type + 1) % 5;
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
        switch (trans_type) {
            case 0: {
                Leap::Vector linearMovement = hand.translation(previous);
                linearMovement *= PT;
                selected->addTransX((int) linearMovement.x);
                selected->addTransY((int) linearMovement.y);
                selected->addTransZ((int) linearMovement.z);
                break;
            }
            case 1: {
                float rotationAroundXAxis = frame.rotationAngle(previous, Vector::xAxis());
                selected->rotateX(rotationAroundXAxis * PR);
                float rotationAroundYAxis = frame.rotationAngle(previous, Vector::yAxis());
                selected->rotateY(rotationAroundYAxis * PR);
                float rotationAroundZAxis = frame.rotationAngle(previous, Vector::zAxis());
                selected->rotateZ(rotationAroundZAxis * PR);
                break;
            }
            case 2: {
                float zoomMotion = hand.scaleFactor(previous);
                selected->scaleX(zoomMotion);
                selected->scaleY(zoomMotion);
                selected->scaleZ(zoomMotion);
                break;
            }
            default:
                break;
        }
    }
}