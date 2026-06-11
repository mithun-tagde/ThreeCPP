target_sources(ThreeCPP PRIVATE
    geometry.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET geometry_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/geometry.h
        ../../include/threecpp/buffer_geometry.h
        ../../include/threecpp/box_geometry.h
)
