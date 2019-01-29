# ******************************************************************************
# This file is part of the "https://github.com/BlackMATov/gba-game"
# For conditions of distribution and use, see copyright notice in LICENSE.md
# Copyright (C) 2019 Matvey Cherevko
# ******************************************************************************

find_package(Boost REQUIRED COMPONENTS
    filesystem program_options)

set(TOOL_NAME "img2gba16b")

file(GLOB_RECURSE TOOL_SOURCES
    sources/*.*)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${TOOL_SOURCES})

add_executable(${TOOL_NAME}
    ${TOOL_SOURCES} ${TOOLBOX_SOURCES})

set_target_properties(${TOOL_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

target_link_libraries(${TOOL_NAME}
    toolbox
    Boost::filesystem
    Boost::program_options)
