target_sources(ThreeCPP PRIVATE
    window.cpp
)

if(THREECPP_PLATFORM_WINDOWS)
    target_sources(ThreeCPP PRIVATE
        windows/win_window.cpp
    )
elseif(THREECPP_PLATFORM_LINUX)
    target_sources(ThreeCPP PRIVATE
        linux/x11_window.cpp
    )
elseif(THREECPP_PLATFORM_MACOS)
    target_sources(ThreeCPP PRIVATE
        macos/cocoa_window.cpp
    )
endif()

target_sources(ThreeCPP PUBLIC
    FILE_SET window_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/window.h
)
