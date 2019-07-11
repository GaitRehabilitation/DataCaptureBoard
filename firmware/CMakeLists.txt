cmake_minimum_required(VERSION 3.13.1)

SET(BOARD_ROOT ${CMAKE_SOURCE_DIR})

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(smart-up)

target_sources(app PRIVATE 
src/main.c 
src/store.c 
src/bt.c
src/gatt/battery_gatt.c
src/gatt/data_logger_gatt.c
src/data_logger.c
src/device_targets.c)

target_include_directories(app PRIVATE src)