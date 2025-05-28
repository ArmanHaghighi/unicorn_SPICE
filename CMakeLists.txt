
cmake_minimum_required(VERSION 3.31)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 26)
find_package(Eigen3 REQUIRED)

add_executable(OOP_Project
        Model/model.cpp
        Model/model.h
        View/view.cpp
        View/view.h
        Controller/controller.cpp
        Controller/controller.h
        main.cpp
        Model/CLI_regexes.cpp
        Model/CLI_regexes.h)
target_link_libraries(OOP_Project Eigen3::Eigen)
