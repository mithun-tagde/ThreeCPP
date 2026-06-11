cmake_minimum_required(VERSION 3.20)
project(ThreeCPP 
    VERSION 0.1.0
    DESCRIPTION "Modern C++ 3D graphics engine inspired by Three.js"
    LANGUAGES CXX
)

# ============= C++ Standard =============
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============= Platform Detection =============
if(WIN32)
    set(THREECPP_PLATFORM_WINDOWS ON)
    message(STATUS "Platform: Windows")
elseif(APPLE)
    set(THREECPP_PLATFORM_MACOS ON)
    message(STATUS "Platform: macOS")
else()
    set(THREECPP_PLATFORM_LINUX ON)
    message(STATUS "Platform: Linux")
endif()

# ============= Feature Toggles =============

# Graphics Backend (mutually exclusive)
option(THREECPP_GRAPHICS_OPENGL "Build OpenGL backend" ON)
option(THREECPP_GRAPHICS_VULKAN "Build Vulkan backend" OFF)
option(THREECPP_GRAPHICS_DIRECTX12 "Build DirectX 12 backend (Windows only)" OFF)

# Optional Feature Modules
option(THREECPP_FEATURES_PHYSICS "Enable physics engine integration" ON)
option(THREECPP_FEATURES_AUDIO "Enable audio support" ON)
option(THREECPP_FEATURES_POSTPROCESSING "Enable post-processing effects" ON)
option(THREECPP_FEATURES_PARTICLES "Enable particle systems" ON)
option(THREECPP_FEATURES_ANIMATION "Enable animation system" ON)
option(THREECPP_FEATURES_SHADOWS "Enable shadow mapping" ON)
option(THREECPP_FEATURES_PBR "Enable PBR materials" ON)

# Build Options
option(THREECPP_BUILD_EXAMPLES "Build example applications" ON)
option(THREECPP_BUILD_TESTS "Build unit tests" ON)
option(THREECPP_ENABLE_ASSERTIONS "Enable debug assertions in Release" ON)

# ============= Validation =============
if(THREECPP_GRAPHICS_DIRECTX12 AND NOT WIN32)
    message(FATAL_ERROR "DirectX 12 backend only available on Windows")
endif()

if(NOT THREECPP_GRAPHICS_OPENGL AND NOT THREECPP_GRAPHICS_VULKAN AND NOT THREECPP_GRAPHICS_DIRECTX12)
    message(FATAL_ERROR "At least one graphics backend must be enabled")
endif()

# ============= Configuration Header =============
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/threecpp/config.h"
)

# Add generated headers to include path
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# ============= Dependencies =============

# GLM for math (header-only)
find_package(glm CONFIG QUIET)
if(NOT glm_FOUND)
    message(STATUS "GLM not found, using FetchContent...")
    include(FetchContent)
    FetchContent_Declare(glm
        URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
    )
    FetchContent_MakeAvailable(glm)
endif()

# GLFW for windowing (if OpenGL enabled)
if(THREECPP_GRAPHICS_OPENGL)
    find_package(glfw3 CONFIG QUIET)
    if(NOT glfw3_FOUND)
        message(STATUS "GLFW not found, using FetchContent...")
        include(FetchContent)
        FetchContent_Declare(glfw
            URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
        )
        FetchContent_MakeAvailable(glfw)
    endif()

    # GLAD for OpenGL loading
    set(THREECPP_GLAD_TARGET)
    find_package(glad CONFIG QUIET)
    if(NOT glad_FOUND)
        message(STATUS "GLAD not found, using FetchContent...")
        include(FetchContent)
        FetchContent_Declare(glad
            URL https://github.com/Dav1dde/glad/archive/refs/tags/v2.0.4.zip
        )
        FetchContent_MakeAvailable(glad)
        add_subdirectory(${glad_SOURCE_DIR}/cmake ${CMAKE_CURRENT_BINARY_DIR}/glad_cmake)
        glad_add_library(glad_gl_core_33 STATIC
            LOADER
            API gl:core=3.3
            LOCATION "${CMAKE_CURRENT_BINARY_DIR}/glad_generated"
        )
        set(THREECPP_GLAD_TARGET glad_gl_core_33)
    else()
        set(THREECPP_GLAD_TARGET glad::glad)
    endif()
endif()

# ============= Build Targets =============

# Core library
add_library(ThreeCPP STATIC)
add_subdirectory(src/core)
add_subdirectory(src/scene)
add_subdirectory(src/camera)
add_subdirectory(src/geometry)
add_subdirectory(src/material)
add_subdirectory(src/mesh)
add_subdirectory(src/light)
add_subdirectory(src/texture)
add_subdirectory(src/window)
add_subdirectory(src/graphics)
add_subdirectory(src/renderer)

# Optional features
if(THREECPP_FEATURES_ANIMATION AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/features/animation/CMakeLists.txt")
    add_subdirectory(src/features/animation)
endif()

if(THREECPP_FEATURES_PARTICLES AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/features/particles/CMakeLists.txt")
    add_subdirectory(src/features/particles)
endif()

if(THREECPP_FEATURES_POSTPROCESSING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/features/postprocessing/CMakeLists.txt")
    add_subdirectory(src/features/postprocessing)
endif()

# Configure main library
target_include_directories(ThreeCPP PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(ThreeCPP PUBLIC glm)

if(THREECPP_GRAPHICS_OPENGL)
    target_link_libraries(ThreeCPP PUBLIC glfw ${THREECPP_GLAD_TARGET})
    if(NOT glad_FOUND)
        target_include_directories(ThreeCPP PUBLIC
            "${CMAKE_CURRENT_BINARY_DIR}/glad_generated/include"
        )
    endif()
endif()

# ============= Documentation Generation (Internal Tool) =============
find_program(PYTHON3 python3 python)

if(PYTHON3)
    add_custom_target(doc_generate
        COMMAND ${PYTHON3} ${CMAKE_SOURCE_DIR}/tools/doc_generator/extract_docs.py
                ${CMAKE_SOURCE_DIR}/include/threecpp
                ${CMAKE_BINARY_DIR}/API_REFERENCE.md
        COMMENT "Generating API documentation from headers..."
        VERBATIM
    )
    
    # Also generate HTML with pandoc if available
    find_program(PANDOC pandoc)
    if(PANDOC)
        add_custom_command(TARGET doc_generate POST_BUILD
            COMMAND ${PANDOC} ${CMAKE_BINARY_DIR}/API_REFERENCE.md 
                    -o ${CMAKE_BINARY_DIR}/API_REFERENCE.html
            COMMENT "Converting documentation to HTML..."
        )
    endif()
    
    message(STATUS "Documentation target available: cmake --build . --target doc_generate")
else()
    message(WARNING "Python 3 not found - documentation generation disabled")
endif()

# ============= Examples =============
if(THREECPP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ============= Tests =============
if(THREECPP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ============= Installation =============
install(TARGETS ThreeCPP
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/threecpp
    DESTINATION include
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/threecpp/config.h"
    DESTINATION include/threecpp
)

# ============= Summary =============
message(STATUS "")
message(STATUS "ThreeCPP Configuration Summary")
message(STATUS "==============================")
message(STATUS "Graphics Backend:")
message(STATUS "  OpenGL:     ${THREECPP_GRAPHICS_OPENGL}")
message(STATUS "  Vulkan:     ${THREECPP_GRAPHICS_VULKAN}")
message(STATUS "  DirectX 12: ${THREECPP_GRAPHICS_DIRECTX12}")
message(STATUS "Features:")
message(STATUS "  Animation:        ${THREECPP_FEATURES_ANIMATION}")
message(STATUS "  Particles:        ${THREECPP_FEATURES_PARTICLES}")
message(STATUS "  Post-processing:  ${THREECPP_FEATURES_POSTPROCESSING}")
message(STATUS "  Shadows:          ${THREECPP_FEATURES_SHADOWS}")
message(STATUS "  PBR Materials:    ${THREECPP_FEATURES_PBR}")
message(STATUS "Build:")
message(STATUS "  Examples: ${THREECPP_BUILD_EXAMPLES}")
message(STATUS "  Tests:    ${THREECPP_BUILD_TESTS}")
message(STATUS "")
