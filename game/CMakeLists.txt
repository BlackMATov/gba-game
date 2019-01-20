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
    -ffast-math\
    -fno-strict-aliasing")

set(CMAKE_CXX_FLAGS "\
    ${CMAKE_C_FLAGS}\
    -fno-rtti\
    -fno-exceptions")

set(CMAKE_C_COMPILER "${DEVKITARM_PATH}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${DEVKITARM_PATH}/bin/arm-none-eabi-g++")

#
# setup executable
#

add_executable(${PROJECT_NAME}.elf
    gbe.hpp
    gbe.cpp
    main.cpp)

set_target_properties(${PROJECT_NAME}.elf PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

add_custom_target(${PROJECT_NAME}.gba ALL
    COMMAND ${DEVKITARM_PATH}/bin/arm-none-eabi-objcopy -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
    COMMAND ${DEVKITPRO_PATH}/tools/bin/gbafix ${PROJECT_NAME}.gba
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Creating GBA ROM ${PROJECT_NAME}.gba")
add_dependencies(${PROJECT_NAME}.gba ${PROJECT_NAME}.elf)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${PROJECT_NAME}.gba)
