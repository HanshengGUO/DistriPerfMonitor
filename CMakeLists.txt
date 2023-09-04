cmake_minimum_required(VERSION 3.10.2)
project(test_monitor LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(rpc_manager)
add_subdirectory(test_monitor)
add_subdirectory(proto)
add_subdirectory(display_monitor)