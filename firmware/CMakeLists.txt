cmake_minimum_required(VERSION 3.13.1)

SET(BOARD_ROOT ${CMAKE_SOURCE_DIR})

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(smart-up)

target_sources(app PRIVATE 
src/main.c 
src/store.c 
src/device_targets.c)