target_sources(ThreeCPP PRIVATE
    gl_device.cpp
)

target_link_libraries(ThreeCPP PRIVATE
    glfw
    glad
)

target_sources(ThreeCPP PUBLIC
    FILE_SET opengl_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../..
    FILES
        gl_device.h
)
