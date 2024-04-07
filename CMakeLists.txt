cmake_minimum_required(VERSION 3.26.3)
project(word_hunt_solver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(RES_DIR ${PROJECT_SOURCE_DIR}/res/)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/)
set(OUTPUT_DIR ${PROJECT_SOURCE_DIR}/out/)


add_executable(word_hunt_solver
    ${SOURCE_DIR}word_hunt_solver/main.cpp
    ${SOURCE_DIR}word_hunt_solver/word_hunt_solver.h
    ${SOURCE_DIR}trie/trie_node.h
    ${SOURCE_DIR}trie/tree.h
)
target_include_directories(word_hunt_solver PRIVATE ${SOURCE_DIR}trie)
target_compile_definitions(word_hunt_solver PRIVATE RES_DIR="${RES_DIR}" OUTPUT_DIR="${OUTPUT_DIR}")

add_executable(dictionary_cleanup ${SOURCE_DIR}utilities/dictionary_cleanup.cpp)
target_compile_definitions(dictionary_cleanup PRIVATE RES_DIR="${RES_DIR}" OUTPUT_DIR="${OUTPUT_DIR}")

add_executable(gen_puzzle_permuatations ${SOURCE_DIR}utilities/permuatation.cpp)
target_compile_definitions(gen_puzzle_permuatations PRIVATE RES_DIR="${RES_DIR}" OUTPUT_DIR="${OUTPUT_DIR}")
