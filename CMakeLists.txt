cmake_minimum_required(VERSION 3.24.0)
project(
    MAGI
    VERSION 0.1.0
    LANGUAGES CXX)

set(target "moru")

include(cmake/CompileOptions.cmake)
include(cmake/Definitions.cmake)
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
            ${MORU_SRC}
)
target_include_directories(
    ${target}
        PRIVATE
            ${MORU_INCLUDE_DIR}
)
target_compile_definitions(
    ${target}
        PRIVATE
            ${MORU_DEFINITIONS}
)
target_link_directories(
    ${target}
        PRIVATE
)
target_link_libraries(
    ${target}
        PRIVATE
            ${MORU_LINK_LIBRARY}
)
target_compile_features(
    ${target}
        PRIVATE
            cxx_std_20
)
target_compile_options(
    ${target}
        PRIVATE
            ${MORU_COMPILE_OPTION}
)
set_target_properties(
    ${target}
        PROPERTIES
            ${MORU_PROPERTY}
)
