#pragma once
/**
 * @class Renderer
 * @brief Main rendering interface
 * 
 * @details
 * High-level rendering API.
 * Abstracts graphics backend selection.
 * Mirrors three.js Renderer.
 */

#include "object3d.h"
#include <memory>

namespace threecpp {

class Scene;
class Camera;

struct RendererConfig {
    int width = 1920;
    int height = 1080;
    std::string title = "ThreeCPP";
    bool vsync = true;
    // Backend selection: 0=OpenGL, 1=Vulkan, 2=DirectX12
    int backend = 0;
};

class Renderer {
public:
    using Ptr = std::shared_ptr<Renderer>;
    
    virtual ~Renderer() = default;
    
    /**
     * @method Render
     * @brief Render scene from camera view
     * 
     * @params
     *   - scene (Scene*): Scene to render
     *   - camera (Camera*): Viewpoint
     */
    virtual void Render(const std::shared_ptr<Scene>& scene, 
                       const std::shared_ptr<Camera>& camera) = 0;
    
    /**
     * @method IsRunning
     * @brief Check if window is still open
     */
    virtual bool IsRunning() const = 0;
    
    /**
     * @method Clear
     * @brief Clear framebuffer
     */
    virtual void Clear() = 0;
    
    /**
     * @method SetSize
     * @brief Change render target size
     */
    virtual void SetSize(int width, int height) = 0;
    
    /**
     * @method GetWidth / GetHeight
     * @brief Get render target dimensions
     */
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
};

/**
 * @function CreateRenderer
 * @brief Create renderer with configuration
 * 
 * @params
 *   - config (const RendererConfig&): Renderer settings
 * 
 * @returns
 *   Renderer instance
 */
Renderer::Ptr CreateRenderer(const RendererConfig& config);

} // namespace threecpp
