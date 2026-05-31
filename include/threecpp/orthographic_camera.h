#pragma once
/**
 * @class OrthographicCamera
 * @brief Orthographic projection camera
 * 
 * @details
 * Camera with no perspective distortion.
 * Useful for 2D rendering and technical drawings.
 * Mirrors three.js OrthographicCamera.
 */

#include "camera.h"

namespace threecpp {

class OrthographicCamera : public Camera {
public:
    using Ptr = std::shared_ptr<OrthographicCamera>;
    
    float left = -1.0f;
    float right = 1.0f;
    float top = 1.0f;
    float bottom = -1.0f;
    
    /**
     * @method OrthographicCamera
     * @brief Constructor
     * 
     * @params
     *   - left, right, top, bottom (float): Viewport bounds
     *   - near (float): Near plane. Default: 0.1
     *   - far (float): Far plane. Default: 1000
     */
    OrthographicCamera(float left = -1, float right = 1, float top = 1, float bottom = -1,
                       float near = 0.1f, float far = 1000.0f);
    
    ~OrthographicCamera() override = default;
    
    Matrix4 GetProjectionMatrix() const override;
    
    const char* GetTypeName() const override {
        return "OrthographicCamera";
    }
};

} // namespace threecpp
