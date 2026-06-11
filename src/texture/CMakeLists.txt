target_sources(ThreeCPP PRIVATE
    texture.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET texture_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/texture.h
)
