cmake_minimum_required(VERSION 3.24.0)
project(
    MAGI
    VERSION 0.1.0
    LANGUAGES CXX)

set(target "ttt")

include(cmake/CompileOptions.cmake)
include(cmake/Dependencies.cmake)
include(cmake/SourceLists.cmake)
include(cmake/Tests.cmake)

add_executable(
    ${target}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
target_sources(
    ${target}
        PRIVATE
            ${MAGI_SRC}
)
target_include_directories(
    ${target}
        PRIVATE
            ${MAGI_INCLUDE_DIR}
)
target_link_libraries(
    ${target}
        PRIVATE
            ${MAGI_LINK_LIBRARY}
)
target_compile_features(
    ${target}
        PRIVATE
            cxx_std_20
)
target_compile_options(
    ${target}
        PRIVATE
            ${MAGI_COMPILE_OPTION}
)
set_target_properties(
    ${target}
        PROPERTIES
            ${MAGI_PROPERTY}
)
