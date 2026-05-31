target_sources(ThreeCPP PRIVATE
    geometry.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET geometry_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/..
    FILES
        ../threecpp/geometry.h
        ../threecpp/buffer_geometry.h
        ../threecpp/box_geometry.h
)
