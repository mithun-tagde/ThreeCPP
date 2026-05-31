target_sources(ThreeCPP PRIVATE
    camera.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET camera_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/..
    FILES
        ../threecpp/camera.h
        ../threecpp/perspective_camera.h
        ../threecpp/orthographic_camera.h
)
