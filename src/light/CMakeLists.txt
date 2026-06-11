target_sources(ThreeCPP PRIVATE
    light.cpp
)

target_sources(ThreeCPP PUBLIC
    FILE_SET light_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/light.h
        ../../include/threecpp/ambient_light.h
        ../../include/threecpp/directional_light.h
)
