target_sources(ThreeCPP PRIVATE
    renderer.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET renderer_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/renderer.h
)
