CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

project(WumpusWorld CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CXXTEST_INCLUDE_DIR "~/cxxtest-4.3/")

add_subdirectory(test)
add_subdirectory(wumpus_world)
