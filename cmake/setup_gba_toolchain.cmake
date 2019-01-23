# ******************************************************************************
# This file is part of the "https://github.com/BlackMATov/gba-game"
# For conditions of distribution and use, see copyright notice in LICENSE.md
# Copyright (C) 2019 Matvey Cherevko
# ******************************************************************************

#
# devkitPro path
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
# devkitARM path
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
# setup toolchain
#

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(GBA_FLAGS "\
    -mthumb-interwork\
    -mthumb\
    -mcpu=arm7tdmi\
    -mtune=arm7tdmi\
    -specs=gba.specs")

set(CMAKE_C_FLAGS "\
    ${GBA_FLAGS}\
    -Wall\
    -Wextra\
    -ffast-math\
    -fno-strict-aliasing")

set(CMAKE_CXX_FLAGS "\
    ${CMAKE_C_FLAGS}\
    -fno-rtti\
    -fno-exceptions")

set(CMAKE_C_COMPILER "${DEVKITARM_PATH}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${DEVKITARM_PATH}/bin/arm-none-eabi-g++")

#
# gba rom target macro
#

function(add_gba_rom_target ELF_NAME)
    set(GBA_ROM_NAME ${ELF_NAME}.gba)
    add_custom_target(${GBA_ROM_NAME} ALL
        COMMAND ${DEVKITARM_PATH}/bin/arm-none-eabi-objcopy -v -O binary ${ELF_NAME} ${GBA_ROM_NAME}
        COMMAND ${DEVKITPRO_PATH}/tools/bin/gbafix ${GBA_ROM_NAME}
        DEPENDS ${ELF_NAME}
        COMMENT "Creating GBA ROM ${GBA_ROM_NAME}")
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${GBA_ROM_NAME})
endfunction(add_gba_rom_target)
