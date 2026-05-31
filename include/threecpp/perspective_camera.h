#pragma once
/**
 * @class PerspectiveCamera
 * @brief Perspective projection camera
 * 
 * @details
 * Standard camera with perspective distortion.
 * Objects further away appear smaller.
 * Mirrors three.js PerspectiveCamera.
 */

#include "camera.h"

namespace threecpp {

class PerspectiveCamera : public Camera {
public:
    using Ptr = std::shared_ptr<PerspectiveCamera>;
    
    /**
     * @property fov
     * @brief Vertical field of view in degrees
     */
    float fov = 75.0f;
    
    /**
     * @property aspect
     * @brief Aspect ratio (width/height)
     */
    float aspect = 16.0f / 9.0f;
    
    /**
     * @method PerspectiveCamera
     * @brief Constructor
     * 
     * @params
     *   - fov (float): Field of view in degrees. Default: 75
     *   - aspect (float): Aspect ratio. Default: 16/9
     *   - near (float): Near plane. Default: 0.1
     *   - far (float): Far plane. Default: 1000
     */
    PerspectiveCamera(float fov = 75.0f, float aspect = 16.0f/9.0f, 
                      float near = 0.1f, float far = 1000.0f);
    
    ~PerspectiveCamera() override = default;
    
    /**
     * @method GetProjectionMatrix
     * @brief Get perspective projection matrix
     */
    Matrix4 GetProjectionMatrix() const override;
    
    const char* GetTypeName() const override {
        return "PerspectiveCamera";
    }
};

} // namespace threecpp
