#pragma once
/**
 * @class MeshPhongMaterial
 * @brief Phong shading material
 * 
 * @details
 * Realistic lighting with ambient, diffuse, and specular components.
 */

#include "material.h"

namespace threecpp {

class MeshPhongMaterial : public Material {
public:
    using Ptr = std::shared_ptr<MeshPhongMaterial>;
    
    /**
     * @property emissive
     * @brief Self-emitted light color
     */
    Color emissive{Color::Black()};
    
    /**
     * @property specular
     * @brief Specular highlight color
     */
    Color specular{Color(0.5f, 0.5f, 0.5f)};
    
    /**
     * @property shininess
     * @brief Specular highlight size (0-100)
     */
    float shininess = 32.0f;
    
    MeshPhongMaterial() = default;
    ~MeshPhongMaterial() override = default;
    
    const char* GetTypeName() const override {
        return "MeshPhongMaterial";
    }
};

} // namespace threecpp
