cmake_minimum_required(VERSION 3.5)
project(Shiro_Bougyo)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Project/Entity.h
        Project/GameState.cpp
        Project/GameState.h
        Project/GameStateManager.cpp
        Project/GameStateManager.h
        Project/Main.cpp
        Project/MenuState.cpp
        Project/MenuState.h
        Project/ObjModel.cpp
        Project/ObjModel.h
        Project/PlayingState.cpp Project/PlayingState.h Project/Camera.h)

add_executable(Shiro_Bougyo ${SOURCE_FILES})

#LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Project/wiiuse/cmake")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/Project/wiiuse/cmake)

#find_package(WiiUse REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Shiro_Bougyo ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



