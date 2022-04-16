cmake_minimum_required(VERSION 3.16)

project(pcd_viewer_pml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Quick3D REQUIRED)
find_package(PCL REQUIRED)

include_directories(
${PCL_INCLUDE_DIRS}
)
add_subdirectory(pcl_reader)
file(GLOB_RECURSE DATA
    ${CMAKE_CURRENT_SOURCE_DIR}/Data/*
)
qt_add_executable(apppcd_viewer_pml
    main.cpp
    ${Data}
)

qt_add_qml_module(apppcd_viewer_pml
    URI pcd_viewer_pml
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(apppcd_viewer_pml PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(apppcd_viewer_pml
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(apppcd_viewer_pml
    PRIVATE Qt6::Quick
    pcl_reader
)

execute_process(
  COMMAND "${CMAKE_COMMAND}" "-E" "create_symlink" ${CMAKE_CURRENT_SOURCE_DIR}/Data ${CMAKE_CURRENT_BINARY_DIR}/Data
)
