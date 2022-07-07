cmake_minimum_required(VERSION 3.14)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(GadgetEditor SHARED
  GadgetEditor_global.h
  GadgetDataModel.cpp
  GadgetDataModel.h
)

target_link_libraries(GadgetEditor PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(GadgetEditor PRIVATE GADGETEDITOR_LIBRARY)
target_include_directories(GadgetEditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
