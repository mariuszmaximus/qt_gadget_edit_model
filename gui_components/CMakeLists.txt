cmake_minimum_required(VERSION 3.1)

##
## PROJECT
## name and version
##
project(gui_componentsMaster VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##
## MAIN_PROJECT CHECK
## determine if deviceconnectdisconnect is built as a subproject (using add_subdirectory) or if it is the main project 
##
set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif()

##
## INCLUDE
##
##
add_subdirectory(src)

option(BuildSampleApp     "Build sample APP." OFF)

if (BuildSampleApp)
    add_subdirectory(example)
endif()

