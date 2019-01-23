cmake_minimum_required(VERSION 3.13)
project(gba-game)

#
# DEVKITPRO_PATH
#

if(DEFINED ENV{DEVKITPRO})
    set(DEVKITPRO_PATH $ENV{DEVKITPRO} CACHE STRING "devkitPro path")
else()
    set(DEVKITPRO_PATH "/opt/devkitpro" CACHE STRING "devkitPro path")
endif()

if(NOT DEVKITPRO_PATH)
    message(FATAL_ERROR "DEVKITPRO_PATH option not set")
endif()

#
# DEVKITARM_PATH
#

if(DEFINED ENV{DEVKITARM})
    set(DEVKITARM_PATH $ENV{DEVKITARM} CACHE STRING "devkitARM path")
else()
    set(DEVKITARM_PATH "/opt/devkitpro/devkitARM" CACHE STRING "devkitARM path")
endif()

if(NOT DEVKITARM_PATH)
    message(FATAL_ERROR "DEVKITARM_PATH option not set")
endif()

#
# subprojects
#

add_subdirectory(game)
