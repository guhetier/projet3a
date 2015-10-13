
project(Memoisation)

SET(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(
    memoisation
    src/fixedPoint.hpp
    src/fixedPoint.cpp
    src/benchmark.cpp
    src/functionTry
)

add_executable(
    test
    src/test.cpp
    src/fixedPoint.hpp
    src/fixedPoint.cpp
    src/functionTry.hpp
)
