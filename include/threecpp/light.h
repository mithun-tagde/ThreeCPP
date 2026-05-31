#pragma once
/**
 * @class Light
 * @brief Base light class
 * 
 * @details
 * Abstract base for all light types.
 * Defines intensity and color.
 */

#include "object3d.h"
#include "color.h"

namespace threecpp {

class Light : public Object3D {
public:
    using Ptr = std::shared_ptr<Light>;
    
    /**
     * @property color
     * @brief Light color
     */
    Color color{Color::White()};
    
    /**
     * @property intensity
     * @brief Light brightness (0-1 or higher for HDR)
     */
    float intensity = 1.0f;
    
    Light();
    ~Light() override = default;
    
    const char* GetTypeName() const override {
        return "Light";
    }
};

} // namespace threecpp
