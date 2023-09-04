#
# Dependencies
#
# find_package(Threads)

#
# Sources
#
set(SOURCES
    main.cpp
    rpc_manager.cpp
)

# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# target_include_directories(server PUBLIC
#   ${PROJECT_SOURCE_DIR}/..
# )
#
# Target
#
add_executable(server ${SOURCES})
target_link_libraries(server
    PUBLIC
    monitor_proto
)
