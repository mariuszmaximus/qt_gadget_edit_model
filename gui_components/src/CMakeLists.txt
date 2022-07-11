cmake_minimum_required(VERSION 3.0)
project(ProjectName)

set(LIB_NAME gui_components)
 

#make sure MOC compiler is called in parallel
set(CMAKE_AUTOGEN_PARALLEL AUTO)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Instruct CMake to create code from Qt resource files (*.qrc)
set(CMAKE_AUTORCC ON)

# UI ==> H generator from QT   # Instruct CMake to create code from Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5OpenGL CONFIG REQUIRED)
find_package(Qt5Charts CONFIG REQUIRED)



aux_source_directory(. SRC_FILES)
#aux_source_directory(data SRC_FILES) 
#aux_source_directory(logic SRC_FILES) 

message(STATUS ${SRC_FILES})

add_library(${LIB_NAME} STATIC ${SRC_FILES})

target_include_directories(${LIB_NAME} PUBLIC .) 

target_link_libraries(${LIB_NAME} Qt5::Widgets) 

