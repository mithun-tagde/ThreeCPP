target_sources(ThreeCPP PRIVATE
    scene.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET scene_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/scene.h
)
