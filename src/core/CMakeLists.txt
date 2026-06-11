set(THREECPP_CORE_SOURCES
    # Math library
    math/vector3.cpp
    math/vector2.cpp
    math/vector4.cpp
    math/matrix4.cpp
    math/quaternion.cpp
    math/color.cpp
    math/euler.cpp
    
    # Core
    object3d.cpp
)

target_sources(ThreeCPP PRIVATE
    ${THREECPP_CORE_SOURCES}
)

# Add headers to public interface
target_sources(ThreeCPP PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/vector2.h
        ../../include/threecpp/vector3.h
        ../../include/threecpp/vector4.h
        ../../include/threecpp/matrix4.h
        ../../include/threecpp/quaternion.h
        ../../include/threecpp/euler.h
        ../../include/threecpp/color.h
        ../../include/threecpp/object3d.h
)
