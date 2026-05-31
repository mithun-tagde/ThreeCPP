#pragma once
/**
 * @class DirectionalLight
 * @brief Directional (sun-like) light
 * 
 * @details
 * Light from a direction (like the sun).
 * Illuminates based on object normal and light direction.
 * Commonly used for main scene lighting.
 */

#include "light.h"

namespace threecpp {

class DirectionalLight : public Light {
public:
    using Ptr = std::shared_ptr<DirectionalLight>;
    
    /**
     * @property target_position
     * @brief Point that light shines toward
     */
    Vector3 target_position{0, 0, 0};
    
    DirectionalLight(const Color& color = Color::White(), float intensity = 1.0f);
    ~DirectionalLight() override = default;
    
    const char* GetTypeName() const override {
        return "DirectionalLight";
    }
};

} // namespace threecpp
