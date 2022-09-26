cmake_minimum_required(VERSION 3.20)
project(Reto_5)

set(CMAKE_CXX_STANDARD 11)

set(BASE_FOLDER programas)

include_directories(./bintree)

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/ejer22.cpp)
    add_executable(ejer22
            ${BASE_FOLDER}/ejer22.cpp
            ${CMAKE_SOURCE_DIR}/bintree/bintree.hxx
            ${CMAKE_SOURCE_DIR}/bintree/node.hxx programas/ejer22.cpp)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/ejer24.cpp)
    add_executable(ejer24
            ${BASE_FOLDER}/ejer24.cpp
            ${CMAKE_SOURCE_DIR}/bintree/bintree.hxx
            ${CMAKE_SOURCE_DIR}/bintree/node.hxx programas/ejer24.cpp)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/ejer30.cpp)
    add_executable(ejer30
            ${BASE_FOLDER}/ejer30.cpp
            ${CMAKE_SOURCE_DIR}/bintree/bintree.hxx
            ${CMAKE_SOURCE_DIR}/bintree/node.hxx programas/ejer30.cpp)
endif()