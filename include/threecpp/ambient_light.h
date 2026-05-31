#pragma once
/**
 * @class AmbientLight
 * @brief Ambient (uniform) lighting
 * 
 * @details
 * Illuminates all surfaces equally from all directions.
 * Useful for base scene lighting without shadows.
 */

#include "light.h"

namespace threecpp {

class AmbientLight : public Light {
public:
    using Ptr = std::shared_ptr<AmbientLight>;
    
    AmbientLight(const Color& color = Color::White(), float intensity = 0.5f);
    ~AmbientLight() override = default;
    
    const char* GetTypeName() const override {
        return "AmbientLight";
    }
};

} // namespace threecpp
