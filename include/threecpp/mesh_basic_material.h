#pragma once
/**
 * @class MeshBasicMaterial
 * @brief Unlit material (no lighting calculation)
 * 
 * @details
 * Renders geometry with flat color, useful for UI and debugging.
 */

#include "material.h"

namespace threecpp {

class MeshBasicMaterial : public Material {
public:
    using Ptr = std::shared_ptr<MeshBasicMaterial>;
    
    MeshBasicMaterial() = default;
    ~MeshBasicMaterial() override = default;
    
    const char* GetTypeName() const override {
        return "MeshBasicMaterial";
    }
};

} // namespace threecpp
