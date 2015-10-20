
project(Memoisation)

SET(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(
    memoisation
    src/fixedPoint.hpp
    src/hash.hpp
    src/benchmark.cpp
    src/functionTry
)

add_executable(
    test
    src/test.cpp
    src/fixedPoint.hpp
    src/hash.hpp
    src/functionTry.hpp
)
