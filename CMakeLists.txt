cmake_minimum_required(VERSION 3.5.0)
project(pxd-stl-c VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

include(setup.cmake)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_BUILD_TYPE "Debug")
else()
set(CMAKE_BUILD_TYPE "Release")
endif()

set(PROJECT_C_STANDARD 99)

enable_iwyu()
enable_avx2()

set(PXD_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party)
set(PXD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes)
set(PXD_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources)

set(PXD_HEADER_FILES
    ${PXD_INCLUDE_DIR}/generic_linked_list.h
    ${PXD_INCLUDE_DIR}/dynamic_array.h
    ${PXD_INCLUDE_DIR}/ring_buffer.h
    ${PXD_INCLUDE_DIR}/hash.h

    ${PXD_THIRD_PARTY_DIR}/blake3/c/blake3.h
)

set(PXD_SOURCE_FILES
    ${PXD_SOURCE_DIR}/generic_linked_list.c
    ${PXD_SOURCE_DIR}/dynamic_array.c
    ${PXD_SOURCE_DIR}/ring_buffer.c
    ${PXD_SOURCE_DIR}/hash.c
)

include_directories(
    ${PXD_INCLUDE_DIR}
    ${PXD_THIRD_PARTY_DIR}
)

set(COMMON_STD_HEADERS
    <stdio.h>
    <stdlib.h>
    <string.h>
    <stdint.h>
)

add_subdirectory(${PXD_THIRD_PARTY_DIR}/blake3/c)

set(LIBS_TO_LINK
    blake3
)

add_library(${PROJECT_NAME} ${PXD_SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD ${PROJECT_C_STANDARD})

target_link_libraries(${PROJECT_NAME} ${LIBS_TO_LINK})

target_precompile_headers(
    ${PROJECT_NAME} PRIVATE
    ${COMMON_STD_HEADERS}
    ${PXD_HEADER_FILES}
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(TEST_PROJECT_NAME pxd-stl-c-test)
    set(PXD_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

    set(PXD_TEST_HEADER_FILES
        ${PXD_HEADER_FILES}

        ${PXD_TEST_DIR}/temp_ds.h
    )

    set(PXD_TEST_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c

        ${PXD_SOURCE_FILES}

        ${PXD_TEST_DIR}/temp_ds.c
    )

    add_executable(${TEST_PROJECT_NAME} ${PXD_TEST_SOURCE_FILES})

    set_target_properties(${TEST_PROJECT_NAME} PROPERTIES C_STANDARD ${PROJECT_C_STANDARD})

    target_link_libraries(${TEST_PROJECT_NAME} ${LIBS_TO_LINK})

    target_precompile_headers(
        ${TEST_PROJECT_NAME} PRIVATE
        ${COMMON_STD_HEADERS}
        ${PXD_HEADER_FILES}
    )

endif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
        