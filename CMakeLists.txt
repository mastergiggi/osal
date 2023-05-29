cmake_minimum_required(VERSION 3.0.0)
project(osal VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

include_directories(inc)
add_executable(osal main.cpp src/os-condvar-std.cpp  src/os-mutex-std.cpp src/os-thread-std.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
