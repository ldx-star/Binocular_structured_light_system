cmake_minimum_required(VERSION 3.25)
project(Binocular_structured_light_system)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Binocular_structured_light_system
        main.cpp Camera.h Camera.cpp types.h utils.h utils.cpp )
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
