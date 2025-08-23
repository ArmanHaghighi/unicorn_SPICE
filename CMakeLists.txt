cmake_minimum_required(VERSION 3.31)
project(OOP_Project VERSION 0.1 LANGUAGES CXX)

# Set Qt-specific settings
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(Eigen3 REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport )

# 🔍 Print Qt version and installation path for debugging
message(STATUS "Qt ${QT_VERSION_MAJOR} found: ${Qt${QT_VERSION_MAJOR}_VERSION}")
message(STATUS "Qt ${QT_VERSION_MAJOR} location: ${Qt${QT_VERSION_MAJOR}_DIR}")

add_definitions(
        -DNOMINMAX
        -DWIN32_LEAN_AND_MEAN
        -DVC_EXTRALEAN
)
# Include directories
include_directories(
        View/spice
        View/spice/cereal/include

)

# Original OOP project sources
set(OOP_SOURCES
        Model/model.cpp
        Model/model.h
        View/view.cpp
        View/view.h
        Controller/controller.cpp
        Controller/controller.h
        main.cpp
        Model/CLI_regexes.cpp
        Model/CLI_regexes.h
        Model/solver.cpp
        Model/solver.h
)

# Spice submodule sources (excluding main.cpp)
set(SPICE_SOURCES
        View/spice/mainwindow.cpp
        View/spice/mainwindow.h
        View/spice/mainwindow.ui
        View/spice/trandialog.cpp
        View/spice/trandialog.h
        View/spice/trandialog.ui
        View/spice/resources.qrc
        View/spice/elements.h
        View/spice/elements.cpp
        View/spice/addelementdialog.h
        View/spice/addelementdialog.cpp
        View/spice/addelementdialog.ui
        View/spice/properties.h
        View/spice/properties.cpp
        View/spice/properties.ui
        View/spice/acdialog.h
        View/spice/acdialog.cpp
        View/spice/acdialog.ui
        View/spice/dcdialog.h
        View/spice/dcdialog.cpp
        View/spice/dcdialog.ui
        View/spice/phasedialog.h
        View/spice/phasedialog.cpp
        View/spice/phasedialog.ui
        View/spice/node.h
        View/spice/node.cpp
        View/spice/wire.h
        View/spice/wire.cpp
        View/spice/qcustomplot.h
        View/spice/qcustomplot.cpp
        View/spice/Scope.h
        View/spice/Scope.cpp

)

# Create executable with all sources
add_executable(OOP_Project
        ${OOP_SOURCES}
        ${SPICE_SOURCES}
)

# Link libraries
target_link_libraries(OOP_Project PRIVATE
        Eigen3::Eigen
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::PrintSupport
)

# Windows-specific properties
set_target_properties(OOP_Project PROPERTIES
        WIN32_EXECUTABLE TRUE
)

# Optional: Install rules (if needed)
include(GNUInstallDirs)
install(TARGETS OOP_Project
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Qt6 finalization (if using Qt6)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(OOP_Project)
endif()