cmake_minimum_required(VERSION 3.7)
project(interactionLeapMotion)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Object3D.cpp Object3D.h Window.cpp Window.h)
add_executable(interactionLeapMotion ${SOURCE_FILES})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(interactionLeapMotion glut GLU GL)