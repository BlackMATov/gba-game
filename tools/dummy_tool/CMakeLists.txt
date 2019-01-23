# ******************************************************************************
# This file is part of the "https://github.com/BlackMATov/gba-game"
# For conditions of distribution and use, see copyright notice in LICENSE.md
# Copyright (C) 2019 Matvey Cherevko
# ******************************************************************************

set(TOOL_NAME "dummy_tool")

file(GLOB TOOL_SOURCES
    sources/*.*)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${TOOL_SOURCES})

add_executable(${TOOL_NAME}
    ${TOOL_SOURCES})

set_target_properties(${TOOL_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)
