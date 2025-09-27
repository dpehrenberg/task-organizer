cmake_minimum_required(VERSION 3.10)
project(TaskOrganizer)

set(CMAKE_CXX_STANDARD 17)

add_executable(run
    main.cpp
    CTask.cpp
    CTaskOrganiser.cpp
)