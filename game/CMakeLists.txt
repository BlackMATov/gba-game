# ******************************************************************************
# This file is part of the "https://github.com/BlackMATov/gba-game"
# For conditions of distribution and use, see copyright notice in LICENSE.md
# Copyright (C) 2019 Matvey Cherevko
# ******************************************************************************

include(setup_gba_toolchain)

set(GAME_NAME "game")

file(GLOB_RECURSE GAME_SOURCES
    sources/*.hpp
    sources/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${GAME_SOURCES})

add_executable(${GAME_NAME}
    ${GAME_SOURCES})

set_target_properties(${GAME_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

add_gba_rom_target(${GAME_NAME})
