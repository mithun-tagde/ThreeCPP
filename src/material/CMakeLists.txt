target_sources(ThreeCPP PRIVATE
    material.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET material_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/..
    FILES
        ../threecpp/material.h
        ../threecpp/mesh_basic_material.h
        ../threecpp/mesh_phong_material.h
)
