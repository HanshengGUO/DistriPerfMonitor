
set(SOURCES
   main.cpp
   monitor/cpu_softirq_monitor.cpp
   monitor/cpu_load_monitor.cpp
   monitor/cpu_stat_monitor.cpp
   monitor/mem_monitor.cpp
   monitor/net_monitor.cpp
   utils/read_file.cpp
)

add_executable(monitor ${SOURCES})

# target_include_directories(monitor PUBLIC
#   ../include/..
# )
target_include_directories(monitor PUBLIC
  ${PROJECT_SOURCE_DIR}/test_monitor/include
  ${PROJECT_SOURCE_DIR}/rpc_manager
)

target_link_libraries(monitor
    PUBLIC
    monitor_proto
    client
    boost_system
    boost_chrono
)