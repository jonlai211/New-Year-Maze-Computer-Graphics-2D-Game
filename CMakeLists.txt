cmake_minimum_required(VERSION 3.23)
project(CPT205)

set(CMAKE_CXX_STANDARD 14)

# GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})

# Assessment1
file(GLOB srcfiles "Assessment1/*.cpp" "Assessment1/*/*.cpp")
add_executable(Assessment1 ${srcfiles})
target_link_libraries(Assessment1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glut)
include_directories(${PROJECT_SOURCE_DIR}/Assessment1/Base)
include_directories(${PROJECT_SOURCE_DIR}/Assessment1/Color)
include_directories(${PROJECT_SOURCE_DIR}/Assessment1/Cube)
include_directories(${PROJECT_SOURCE_DIR}/Assessment1/Firework)
include_directories(${PROJECT_SOURCE_DIR}/Assessment1/GlobalState)
include_directories(${PROJECT_SOURCE_DIR}/Assessment1/main)
include_directories(${PROJECT_SOURCE_DIR}/Assessment1/Mouse)
include_directories(${PROJECT_SOURCE_DIR}/Assessment1/Phone)
include_directories(${PROJECT_SOURCE_DIR}/Assessment1/random)