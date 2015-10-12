
project(Memoisation)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

add_executable(
    countingBlocks
    ../Cpp/src/fixedPoint.hpp
    src/countingBlocks.cpp
)

add_executable(
    RGBTilesNoMerge
    src/RGBTilesNoMergeTwoArgs.cpp
    ../Cpp/src/fixedPoint.hpp
)

add_executable(
    RGBTiles
    src/RGBTiles.cpp
    ../Cpp/src/fixedPoint.hpp
)
