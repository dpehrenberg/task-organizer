cmake_minimum_required(VERSION 3.10)
project(TaskOrganizer)

set(CMAKE_CXX_STANDARD 17)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_executable(run
    main.cpp
    CTask.cpp
    CTaskOrganiser.cpp
)

# Create custom targets for release and debug builds
add_custom_target(release
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release -S ${CMAKE_SOURCE_DIR} -B ${CMAKE_BINARY_DIR}/release
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/release
)

add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug -S ${CMAKE_SOURCE_DIR} -B ${CMAKE_BINARY_DIR}/debug
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/debug
)
