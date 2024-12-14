cmake_minimum_required(VERSION 3.8)

project(intp_cli)

add_executable(
    intp_cli
    main_cli.cpp
    interpolators/fourier.cpp
    interpolators/fourier.h
    interpolators/linear.cpp
    interpolators/linear.cpp
    interpolators/lanczos.h
    interpolators/lanczos.cpp
)
