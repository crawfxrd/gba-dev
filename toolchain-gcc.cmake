# SPDX-License-Identifier: MPL-2.0

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if(NOT DEFINED DEVKITPRO_ROOT_DIR)
    set(DEVKITPRO_ROOT_DIR "$ENV{DEVKITPRO}")
endif()
if(NOT IS_DIRECTORY "${DEVKITPRO_ROOT_DIR}")
    message(FATAL_ERROR "devkitPro not found")
endif()

if(NOT DEFINED DEVKITARM_ROOT_DIR)
    set(DEVKITARM_ROOT_DIR "$ENV{DEVKITARM}")
endif()
if(NOT IS_DIRECTORY "${DEVKITARM_ROOT_DIR}")
    message(FATAL_ERROR "devkitARM not found")
endif()

set(CMAKE_PREFIX_PATH
    "${DEVKITARM_ROOT_DIR}"
    "${DEVKITPRO_ROOT_DIR}/tools")

set(TOOLCHAIN_PREFIX arm-none-eabi-)
set(CMAKE_C_COMPILER "${DEVKITARM_ROOT_DIR}/bin/${TOOLCHAIN_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${DEVKITARM_ROOT_DIR}/bin/${TOOLCHAIN_PREFIX}g++")
set(CMAKE_LINKER "${DEVKITARM_ROOT_DIR}/bin/${TOOLCHAIN_PREFIX}ld")
set(CMAKE_AR "${DEVKITARM_ROOT_DIR}/bin/${TOOLCHAIN_PREFIX}ar")
set(CMAKE_OBJCOPY "${DEVKITARM_ROOT_DIR}/bin/${TOOLCHAIN_PREFIX}objcopy")

set(_arch_flags "-mthumb -mthumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi")
set(_common_flags "${_arch_flags} -Wall -Wextra")
set(_c_flags "-fno-common")
set(_cxx_flags "-fno-rtti -fno-exceptions -fno-asynchronous-unwind-tables")
set(_debug_flags "-g -O0")
set(_release_flags "-O3 -fomit-frame-pointer -ffast-math")

set(CMAKE_C_FLAGS_INIT "${_common_flags} ${_c_flags}")
set(CMAKE_C_FLAGS_DEBUG_INIT "${_debug_flags}")
set(CMAKE_C_FLAGS_RELEASE_INIT "${_release_flags}")

set(CMAKE_CXX_FLAGS_INIT "${_common_flags} ${_cxx_flags}")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "${_debug_flags}")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "${_release_flags}")

set(CMAKE_ASM_FLAGS_INIT "${_arch_flags} -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-specs=gba.specs")
