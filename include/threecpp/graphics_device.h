#pragma once
/**
 * @file graphics_device.h
 * @brief Graphics Hardware Abstraction Layer (HAL)
 * 
 * @details
 * Abstract interface for graphics backends (OpenGL, Vulkan, DirectX12).
 * All graphics operations go through this interface.
 * Allows swapping rendering backends without changing engine code.
 */

#include <memory>
#include <string>
#include <glm/glm.hpp>

namespace threecpp::graphics {

enum class GraphicsAPI { OpenGL, Vulkan, DirectX12 };

/**
 * @struct BufferDesc
 * @brief Buffer creation parameters
 */
struct BufferDesc {
    enum class Type { Vertex, Index, Uniform, Storage };
    Type type;
    size_t size;
    const void* initial_data = nullptr;
};

/**
 * @struct TextureDesc
 * @brief Texture creation parameters
 */
struct TextureDesc {
    int width, height;
    enum class Format { RGB, RGBA, Depth, Normal };
    Format format;
    const void* initial_data = nullptr;
};

/**
 * @class Buffer
 * @brief GPU buffer (vertex, index, uniform, etc.)
 */
class Buffer {
public:
    virtual ~Buffer() = default;
    virtual void UpdateData(const void* data, size_t offset, size_t size) = 0;
};

/**
 * @class Texture
 * @brief GPU texture resource
 */
class Texture {
public:
    virtual ~Texture() = default;
    virtual void UpdateData(const void* data) = 0;
};

/**
 * @class Shader
 * @brief GPU shader program
 */
class Shader {
public:
    virtual ~Shader() = default;
};

/**
 * @class Framebuffer
 * @brief Render target (color + depth)
 */
class Framebuffer {
public:
    virtual ~Framebuffer() = default;
};

/**
 * @class GraphicsDevice
 * @brief Main graphics API abstraction
 */
class GraphicsDevice {
public:
    virtual ~GraphicsDevice() = default;
    
    virtual GraphicsAPI GetAPI() const = 0;
    virtual const std::string& GetVendor() const = 0;
    
    // Resource creation
    virtual std::unique_ptr<Buffer> CreateBuffer(const BufferDesc& desc) = 0;
    virtual std::unique_ptr<Texture> CreateTexture(const TextureDesc& desc) = 0;
    virtual std::unique_ptr<Shader> CreateShader(const std::string& vs_source, 
                                                 const std::string& fs_source) = 0;
    virtual std::unique_ptr<Framebuffer> CreateFramebuffer(int width, int height) = 0;
    
    // Frame management
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void Present() = 0;
    
    // State management
    virtual void SetViewport(int x, int y, int w, int h) = 0;
    virtual void Clear(const glm::vec4& color, float depth) = 0;
    virtual void DrawIndexed(uint32_t index_count, uint32_t first_index) = 0;
};

} // namespace threecpp::graphics
