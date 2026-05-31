target_sources(ThreeCPP PRIVATE
    light.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET light_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/..
    FILES
        ../threecpp/light.h
        ../threecpp/ambient_light.h
        ../threecpp/directional_light.h
)
