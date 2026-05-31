#pragma once
/**
 * @class Camera
 * @brief Base camera class
 * 
 * @details
 * Abstract base class for all camera types.
 * Defines view and projection matrices.
 */

#include "object3d.h"

namespace threecpp {

class Camera : public Object3D {
public:
    using Ptr = std::shared_ptr<Camera>;
    
    /**
     * @property near
     * @brief Near clipping plane
     */
    float near = 0.1f;
    
    /**
     * @property far
     * @brief Far clipping plane
     */
    float far = 1000.0f;
    
    /**
     * @method Camera
     * @brief Base constructor (protected, use derived classes)
     */
    Camera();
    
    ~Camera() override = default;
    
    /**
     * @method GetProjectionMatrix
     * @brief Get projection matrix
     */
    virtual Matrix4 GetProjectionMatrix() const = 0;
    
    /**
     * @method GetViewMatrix
     * @brief Get view (inverse world) matrix
     */
    Matrix4 GetViewMatrix() const;
    
    const char* GetTypeName() const override {
        return "Camera";
    }
};

} // namespace threecpp
