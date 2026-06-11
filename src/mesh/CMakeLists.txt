target_sources(ThreeCPP PRIVATE
    mesh.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET mesh_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/mesh.h
)
