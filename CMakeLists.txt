cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
  advent-of-code
  VERSION 0.1.0
  DESCRIPTION "Advent of code exercises for the 2022 version"
  HOMEPAGE_URL "https://adventofcode.com/2022"
  LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
  aoc_lib
  OBJECT
  source/step1.cpp
  source/utils.cpp
  source/day2.hpp
  source/day2.cpp
)

target_include_directories(
  aoc_lib ${warning_guard}
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(aoc_lib PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
target_link_libraries(aoc_lib PRIVATE fmt::fmt Microsoft.GSL::GSL)

# ---- Developer mode ----

if (NOT aoc_DEVELOPER_MODE)
  return()
elseif (NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING
    "Developer mode is intended for developers of advent-of-code"
  )
endif ()

include(cmake/dev-mode.cmake)
