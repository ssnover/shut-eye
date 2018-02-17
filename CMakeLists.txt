cmake_minimum_required(VERSION 3.0)
project(bt-record)

set(MY_SOURCE_DIRECTORY bluetooth-recorder)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lble++")

include_directories(/home/ssnover/develop/libblepp)
link_directories(/usr/local/lib
                /usr/lib/x86_64-linux-gnu)

set(HEADER_FILES
        )

set(SOURCE_FILES
        ${MY_SOURCE_DIRECTORY}/main.cpp
        ${HEADER_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ble++ bluetooth)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)