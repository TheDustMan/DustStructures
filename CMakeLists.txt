project(DustStructures)
cmake_minimum_required(VERSION 3.16)

add_compile_options(-std=c++17 -g)
include_directories(include)
file(
  GLOB_RECURSE PROJECT_SOURCES
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  src/*.cpp
)
add_executable(trier
  bin/trie_driver.cpp
  ${PROJECT_SOURCES}
)

enable_testing()
file(
  GLOB_RECURSE TEST_SOURCES
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  test/*.h
  test/*.hpp
  test/*.cpp
)
add_executable(
  ${PROJECT_NAME}-test-unit
  ${TEST_SOURCES}
  ${PROJECT_SOURCES}
)
target_include_directories(
  ${PROJECT_NAME}-test-unit
  SYSTEM
  PRIVATE  
  doctest
)
  
