cmake_minimum_required(VERSION 3.7)
project(interactiveObject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Object3D.cpp Object3D.h Window.cpp Window.h IOObjects.cpp IOObjects.h LeapListener.cpp LeapListener.h)
add_executable(interactiveObject ${SOURCE_FILES})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(interactiveObject glut GLU GL Leap)