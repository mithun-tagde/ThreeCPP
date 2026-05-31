#pragma once
/**
 * @class Texture
 * @brief 2D texture for surface mapping
 * 
 * @details
 * Image data applied to surfaces.
 * Used for diffuse maps, normal maps, etc.
 */

#include <memory>
#include <string>

namespace threecpp {

class Texture {
public:
    using Ptr = std::shared_ptr<Texture>;
    
    /**
     * @property name
     * @brief Texture name for identification
     */
    std::string name;
    
    virtual ~Texture() = default;
    
    virtual const char* GetTypeName() const {
        return "Texture";
    }
};

} // namespace threecpp
