# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(aocTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(GTest REQUIRED)
include(GoogleTest)

# ---- Tests ----

# disable clang-tidy for unit test code
if (DEFINED CMAKE_CXX_CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY "")
endif ()

add_executable(
  aoc_test
  source/advent_tests_day1.cpp
  source/advent_tests_utils.cpp
  source/advent_tests_day2.cpp
  source/advent_tests_day3.cpp
  source/advent_tests_day4.cpp
  source/advent_tests_day5.cpp
  source/advent_tests_day6.cpp
  source/advent_tests_day7.cpp
  source/advent_tests_day8.cpp
)
target_link_libraries(
  aoc_test PRIVATE
  aoc_lib
  GTest::gtest_main
)
target_compile_features(aoc_test PRIVATE cxx_std_20)

gtest_discover_tests(aoc_test)

# ---- End-of-file commands ----

add_folders(Test)
