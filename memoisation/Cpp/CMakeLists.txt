
project(Memoisation)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

add_executable(
    memoisation
    src/fixedPoint.hpp
    src/fixedPoint.cpp
    src/benchmark.cpp
)
