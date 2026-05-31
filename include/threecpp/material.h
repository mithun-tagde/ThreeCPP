#pragma once
/**
 * @class Material
 * @brief Base material class
 * 
 * @details
 * Defines how surfaces are rendered.
 * Base class for all material types.
 */

#include "color.h"
#include <memory>

namespace threecpp {

class Material {
public:
    using Ptr = std::shared_ptr<Material>;
    
    /**
     * @property color
     * @brief Base color/albedo
     */
    Color color{Color::White()};
    
    /**
     * @property wireframe
     * @brief Render as wireframe
     */
    bool wireframe = false;
    
    /**
     * @property side
     * @brief Which side to render (0=front, 1=back, 2=both)
     */
    int side = 0;  // Front
    
    virtual ~Material() = default;
    
    virtual const char* GetTypeName() const {
        return "Material";
    }
};

} // namespace threecpp
