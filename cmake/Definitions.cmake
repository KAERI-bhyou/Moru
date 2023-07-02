if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(MORU_DEFINITIONS
        "TBB_USE_DEBUG"
        "_WIN32_WINNT=0x0601"
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(MORU_DEFINITIONS
        "_WIN32_WINNT=0x0601"
    )
endif()
