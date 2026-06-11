# Graphics backends
if(THREECPP_GRAPHICS_OPENGL)
    add_subdirectory(opengl)
endif()

if(THREECPP_GRAPHICS_VULKAN)
    add_subdirectory(vulkan)
endif()

if(THREECPP_GRAPHICS_DIRECTX12)
    add_subdirectory(directx)
endif()

# HAL interface (always needed)
target_sources(ThreeCPP PUBLIC
    FILE_SET graphics_hal_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    FILES
        ../../include/threecpp/graphics_device.h
)
