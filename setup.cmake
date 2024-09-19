function(set_debug)
    IF(NOT MSVC)
        set(CMAKE_BUILD_TYPE "Debug")
    ENDIF(NOT MSVC)
endfunction(set_debug)

function(set_release)
    IF(NOT MSVC)
        set(CMAKE_BUILD_TYPE "Release")
    ENDIF(NOT MSVC)
endfunction(set_release)

function(enable_avx2)
    # from glm repository's CMakeLists.txt
    if((CMAKE_C_COMPILER_ID MATCHES "GNU") OR (CMAKE_C_COMPILER_ID MATCHES "Clang"))
        add_compile_options(-mavx2)
    elseif(CMAKE_C_COMPILER_ID MATCHES "Intel")
        add_compile_options(/QxAVX2)
    elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
        add_compile_options(/arch:AVX2)
    endif()
endfunction(enable_avx2)

function(enable_sse4_2)
    # from glm repository's CMakeLists.txt
    if((CMAKE_C_COMPILER_ID MATCHES "GNU") OR (CMAKE_C_COMPILER_ID MATCHES "Clang"))
        add_compile_options(-msse4.2)
    elseif(CMAKE_C_COMPILER_ID MATCHES "Intel")
        add_compile_options(/QxSSE4.2)
    elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
        add_compile_options(/arch:SSE2)
    endif()
endfunction(enable_sse4_2)

function(enable_iwyu)
    if(NOT WIN32)
        set(IWYU_ARGS include-what-you-use -w -Xiwyu --verbose=7)
        add_compile_definitions(CMAKE_C_INCLUDE_WHAT_YOU_USE=${IWYU_ARGS})
    endif(NOT WIN32)
endfunction(enable_iwyu)

function(is_main_project value)
    set(value (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR}))
endfunction(is_main_project)

            