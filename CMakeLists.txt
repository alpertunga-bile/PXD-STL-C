cmake_minimum_required(VERSION 3.5.0)
project(pxd-stl-c VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include(setup.cmake)

set_c(99)
enable_iwyu()
enable_avx2()

set(PXD_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party)
set(PXD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes)
set(PXD_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources)

set(PXD_HEADER_FILES
    ${PXD_INCLUDE_DIR}/generic_linked_list.h
    ${PXD_INCLUDE_DIR}/dynamic_array.h
)

set(PXD_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c

    ${PXD_SOURCE_DIR}/generic_linked_list.c
    ${PXD_SOURCE_DIR}/dynamic_array.c
)

include_directories(
)

set(COMMON_STD_HEADERS
    <stdio.h>
    <stdlib.h>
    <string.h>
)

set(LIBS_TO_LINK
)

add_executable(${PROJECT_NAME} ${PXD_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBS_TO_LINK})

target_precompile_headers(
    ${PROJECT_NAME} PRIVATE
    ${COMMON_STD_HEADERS}
    ${PXD_HEADER_FILES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
        