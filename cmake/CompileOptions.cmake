if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    message(STATUS "Compiler")
    message(STATUS " - ID       \t: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS " - Version  \t: ${CMAKE_CXX_COMPILER_VERSION}")
    message(STATUS " - Path     \t: ${CMAKE_CXX_COMPILER}")
    message(STATUS " - OS       \t: ${CMAKE_SYSTEM}")
    message(STATUS " - Type     \t: ${CMAKE_BUILD_TYPE}")

    if(WIN32)
        set(MAGI_DEFAULT_COMPILE_OPTION
            "/fp:strict"
            "-Wno-deprecated-builtins"
        )
        set(MAGI_DEFAULT_PROPERTY
            CXX_EXTENSIONS OFF
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
        )
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG:FULL /INCREMENTAL:NO /MANIFEST:NO")
            set(MAGI_COMPILE_OPTION
                ${MAGI_DEFAULT_COMPILE_OPTION}
                "/debug:full"
            )
            set(MAGI_PROPERTY
                ${MAGI_DEFAULT_PROPERTY}
            )
        elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /INCREMENTAL:NO /MANIFEST:NO")
            set(MAGI_COMPILE_OPTION
                ${MAGI_DEFAULT_COMPILE_OPTION}
                "/O2"
            )
            set(MAGI_PROPERTY
                ${MAGI_DEFAULT_PROPERTY}
            )
        endif()
    elseif(UNIX)
        set(MAGI_DEFAULT_COMPILE_OPTION
            "-fp-model=strict"
        )
        set(MAGI_DEFAULT_PROPERTY
            CXX_EXTENSIONS OFF
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
        )
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(MAGI_COMPILE_OPTION
                ${MAGI_DEFAULT_COMPILE_OPTION}
                "-g"
                "-Og"
            )
            set(MAGI_PROPERTY
                ${MAGI_DEFAULT_PROPERTY}
            )
        elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
            set(MAGI_COMPILE_OPTION
                ${MAGI_DEFAULT_COMPILE_OPTION}
                "-O2"
            )
            set(MAGI_PROPERTY
                ${MAGI_DEFAULT_PROPERTY}
            )
        endif()
    else()
        message(STATUS " - Unsupported OS")
    endif()
else()
    message(STATUS " - Unsupported Compiler")
endif()
