# ******************************************************************************
# This file is part of the "https://github.com/BlackMATov/gba-game"
# For conditions of distribution and use, see copyright notice in LICENSE.md
# Copyright (C) 2019 Matvey Cherevko
# ******************************************************************************

set(TOOLBOX_NAME "toolbox")

file(GLOB_RECURSE TOOLBOX_SOURCES
    headers/*.*
    sources/*.*)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${TOOLBOX_SOURCES})

add_library(${TOOLBOX_NAME} STATIC
    ${TOOLBOX_SOURCES})

set_target_properties(${TOOLBOX_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

target_include_directories(${TOOLBOX_NAME}
    PUBLIC headers)
