#pragma once
/**
 * @class Scene
 * @brief Container for all 3D objects in a scene
 * 
 * @details
 * Root of the scene graph. Contains all objects to be rendered.
 * Mirrors three.js Scene class.
 */

#include "object3d.h"

namespace threecpp {

class Scene : public Object3D {
public:
    using Ptr = std::shared_ptr<Scene>;
    
    /**
     * @method Scene
     * @brief Default constructor
     */
    Scene();
    
    ~Scene() override = default;
    
    /**
     * @method GetTypeName
     * @brief Type identification
     */
    const char* GetTypeName() const override {
        return "Scene";
    }
    
    std::string ToString() const override;
};

} // namespace threecpp
