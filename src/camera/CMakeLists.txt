target_sources(ThreeCPP PRIVATE
    camera.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET camera_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/camera.h
        ../../include/threecpp/perspective_camera.h
        ../../include/threecpp/orthographic_camera.h
)
