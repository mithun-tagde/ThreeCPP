target_sources(ThreeCPP PRIVATE
    material.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET material_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/material.h
        ../../include/threecpp/mesh_basic_material.h
        ../../include/threecpp/mesh_phong_material.h
)
