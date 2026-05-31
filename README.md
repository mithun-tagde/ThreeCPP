# ThreeCPP - Modern C++ 3D Graphics Engine

[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Windows](https://img.shields.io/badge/Platform-Windows-blue.svg)]()
[![Linux](https://img.shields.io/badge/Platform-Linux-red.svg)]()
[![macOS](https://img.shields.io/badge/Platform-macOS-lightgrey.svg)]()

ThreeCPP is a modern C++20 3D graphics engine inspired by [Three.js](https://threejs.org/), providing an intuitive API for 3D graphics while supporting multiple rendering backends (OpenGL, Vulkan, DirectX 12) and platforms (Windows, Linux, macOS).

## Features

✨ **Three.js API Parity** - Familiar API for developers coming from web graphics  
🎨 **Multi-Backend Support** - OpenGL, Vulkan, DirectX 12 backends  
🖥️ **Cross-Platform** - Windows, Linux, macOS with unified codebase  
📚 **Modern C++** - C++20 with smart pointers, concepts, and zero-overhead abstractions  
🔌 **Modular Architecture** - Enable/disable features at compile time  
⚡ **Performance-First** - Optimized rendering pipeline  
🎯 **Scene Graph** - Hierarchical object management with transforms  
💡 **Lighting System** - Ambient, directional, point, and spot lights  
🎭 **Materials** - Basic, Phong, and PBR materials (extensible)  
📦 **Extensible** - Easy to add new backends, materials, and features  

## Quick Start

### Prerequisites

- C++20 compiler (GCC 11+, Clang 13+, MSVC 2019+)
- CMake 3.20+
- OpenGL 4.5+ (for OpenGL backend)

### Build

```bash
git clone https://github.com/yourusername/ThreeCPP.git
cd ThreeCPP
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Basic Example

```cpp
#include <threecpp/threecpp.h>
using namespace threecpp;

int main() {
    // Create renderer
    RendererConfig config;
    config.width = 1920;
    config.height = 1080;
    auto renderer = CreateRenderer(config);
    
    // Create scene and camera
    auto scene = std::make_shared<Scene>();
    auto camera = std::make_shared<PerspectiveCamera>(75, 16.0f/9.0f, 0.1f, 1000);
    camera->position = Vector3(0, 0, 5);
    
    // Create mesh
    auto geometry = std::make_shared<BoxGeometry>(1, 1, 1);
    auto material = std::make_shared<MeshPhongMaterial>();
    material->color = Color(0xFF0000);  // Red
    auto mesh = std::make_shared<Mesh>(geometry, material);
    scene->Add(mesh);
    
    // Add lighting
    auto light = std::make_shared<DirectionalLight>(Color::White(), 1.0f);
    light->position = Vector3(5, 5, 5);
    scene->Add(light);
    
    // Render loop
    while (renderer->IsRunning()) {
        // Animate
        mesh->rotation.x += 0.01f;
        mesh->rotation.y += 0.01f;
        
        // Render
        renderer->Render(scene, camera);
    }
    
    return 0;
}
```

## Configuration

### Select Graphics Backend

```bash
# OpenGL (default)
cmake .. -DTHREECPP_GRAPHICS_OPENGL=ON

# Vulkan
cmake .. -DTHREECPP_GRAPHICS_VULKAN=ON -DTHREECPP_GRAPHICS_OPENGL=OFF

# DirectX 12 (Windows only)
cmake .. -DTHREECPP_GRAPHICS_DIRECTX12=ON -DTHREECPP_GRAPHICS_OPENGL=OFF
```

### Disable Optional Features

```bash
cmake .. -DTHREECPP_FEATURES_PARTICLES=OFF \
         -DTHREECPP_FEATURES_ANIMATION=OFF \
         -DTHREECPP_FEATURES_POSTPROCESSING=OFF
```

### Build Options

```bash
# Disable examples
cmake .. -DTHREECPP_BUILD_EXAMPLES=OFF

# Disable tests
cmake .. -DTHREECPP_BUILD_TESTS=OFF
```

## Architecture

### Graphics Hardware Abstraction (HAL)

The entire graphics system is abstracted behind a clean interface, allowing backends to be swapped without changing engine code:

```
Your Application Code
        ↓
   ThreeCPP Engine (Scene, Materials, Lighting)
        ↓
Graphics HAL Interface (Pure Virtual)
        ↓
┌───────────────────────────────────────┐
│ OpenGL │ Vulkan │ DirectX 12 │ Future │
└───────────────────────────────────────┘
```

### Directory Structure

```
ThreeCPP/
├── src/
│   ├── core/              # Math, Object3D, transforms
│   ├── scene/             # Scene graph management
│   ├── camera/            # Camera types
│   ├── geometry/          # Geometry definitions
│   ├── material/          # Material system
│   ├── mesh/              # Mesh rendering
│   ├── light/             # Lighting
│   ├── texture/           # Texture management
│   ├── renderer/          # Rendering pipeline
│   ├── graphics/          # Backend implementations
│   │   ├── hal/           # HAL interfaces
│   │   ├── opengl/        # OpenGL backend
│   │   ├── vulkan/        # Vulkan backend
│   │   └── directx/       # DirectX 12 backend
│   ├── window/            # Window management
│   └── features/          # Optional features
├── include/threecpp/      # Public headers
├── examples/              # Example applications
├── tests/                 # Unit tests
├── tools/                 # Developer tools
└── CMakeLists.txt
```

## API Parity with Three.js

ThreeCPP provides API-compatible versions of common Three.js classes:

| Three.js | ThreeCPP | Notes |
|----------|----------|-------|
| `THREE.Scene()` | `threecpp::Scene()` | Scene root |
| `THREE.PerspectiveCamera()` | `threecpp::PerspectiveCamera()` | Camera |
| `THREE.BoxGeometry()` | `threecpp::BoxGeometry()` | Box shape |
| `THREE.MeshPhongMaterial()` | `threecpp::MeshPhongMaterial()` | Material |
| `THREE.Mesh()` | `threecpp::Mesh()` | Renderable object |
| `THREE.Vector3()` | `threecpp::Vector3()` | 3D vector |
| `THREE.Matrix4()` | `threecpp::Matrix4()` | 4x4 matrix |
| `THREE.Quaternion()` | `threecpp::Quaternion()` | Rotation |
| `THREE.Color()` | `threecpp::Color()` | Color |

Web developers familiar with Three.js can immediately start using ThreeCPP with minimal learning curve.

## Building From Source

### Windows (MSVC 2019+)

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
```

### Linux (GCC 11+)

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

### macOS (Clang 13+)

```bash
mkdir build
cd build
cmake -GXcode
cmake --build . --config Release
```

## Examples

See `examples/` directory for complete working examples:

- `01_hello_triangle.cpp` - Minimal triangle rendering
- `02_cube_rotation.cpp` - Animated rotating cube
- `03_lighting.cpp` - Multiple light types
- `04_texture_mapping.cpp` - Textured surfaces

## Documentation

### API Reference

Generate API documentation from headers:

```bash
cd build
cmake --build . --target doc_generate
# View: API_REFERENCE.md or API_REFERENCE.html (with Pandoc)
```

### Inline Documentation

All classes and methods are documented with structured comments:

```cpp
/**
 * @method Add
 * @brief Add child object(s)
 * 
 * @params
 *   - child (const Ptr&): Child object to add
 * 
 * @returns
 *   (Ptr) Returns this for chaining
 * 
 * @example
 * ```cpp
 * parent->Add(child1)->Add(child2);
 * ```
 */
```

## Performance Considerations

- **Transformations**: Local → world matrix propagation is O(depth)
- **Rendering**: Batch similar geometry to reduce draw calls
- **Memory**: Use `shared_ptr` for automatic lifetime management
- **GPU**: Batch transforms with instancing for repeated objects

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Make changes with tests
4. Submit a pull request

## Future Roadmap

- ✅ Core rendering infrastructure
- ⏳ Vulkan backend
- ⏳ DirectX 12 backend
- ⏳ PBR materials
- ⏳ Particle systems
- ⏳ Post-processing effects
- ⏳ Physics integration
- ⏳ Animation system
- ⏳ Skeletal animation
- ⏳ Audio support
- ⏳ Serialization (glTF, FBX)
- ⏳ Scene editor (Qt-based)

## Technical Stack

| Component | Choice | Version |
|-----------|--------|---------|
| C++ Standard | C++ | 20/23 |
| Build System | CMake | 3.20+ |
| Math | GLM | 0.9.9+ |
| Window | GLFW | 3.4+ |
| OpenGL | GLAD | 2.0.0+ |
| Testing | Catch2 | 3.0+ |

## Performance Tips

1. **Frustum Culling** - Only render visible objects
2. **Batch Rendering** - Combine similar meshes
3. **Level of Detail** - Reduce geometry complexity at distance
4. **Texture Atlasing** - Combine textures into single atlas
5. **Spatial Partitioning** - Use octrees for large scenes

## License

MIT License - see [LICENSE](LICENSE) file

## Authors

- **Mithun** - Initial architecture and implementation

## Acknowledgments

- [Three.js](https://threejs.org/) - Inspiration for API design
- [GLM](https://glm.g-truc.net/) - Math library
- [GLFW](https://www.glfw.org/) - Window management
- OpenGL/Vulkan/DirectX communities

---

**Status:** Pre-release (Phase 1: Foundation) 🚀

For questions, issues, or contributions, visit the [GitHub repository](https://github.com/yourusername/ThreeCPP).
