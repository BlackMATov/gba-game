#
# setup toolchain
#

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(GBA_ARCH "-mthumb-interwork -mthumb")
set(GBA_SPECS "-specs=gba.specs")

set(CMAKE_C_FLAGS "${GBA_ARCH} ${GBA_SPECS} -O2 -Wall -fno-strict-aliasing")
set(CMAKE_CXX_FLAGS "${GBA_ARCH} ${GBA_SPECS} -O2 -Wall -fno-strict-aliasing")

set(CMAKE_C_COMPILER "${DEVKITARM_PATH}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${DEVKITARM_PATH}/bin/arm-none-eabi-g++")

#
# setup executable
#

add_executable(${PROJECT_NAME}.elf
    main.c)

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
