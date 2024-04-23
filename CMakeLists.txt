project(image_processor CXX)
set(CMAKE_CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.8)

add_executable(
        image_processor
        image_processor.cpp
        image.cpp crop.cpp GrayScale.cpp Negative.cpp
        GrayScale.cpp GrayScale.cpp GrayScale.cpp GrayScale.cpp
        file_load.cpp parser.cpp multifilter.cpp edge.cpp Blur.cpp Vignette.cpp)
