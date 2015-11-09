
project(Memoisation)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

add_executable(
    memoisation
    src/fixedPoint.hpp
    src/benchmark.cpp
)

add_executable(
    test
    src/fixedPoint.hpp
    src/test.cpp
)
