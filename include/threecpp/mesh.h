#pragma once
/**
 * @class Mesh
 * @brief Renderable mesh combining geometry and material
 * 
 * @details
 * The main renderable object in 3D scenes.
 * Combines a Geometry (shape) with a Material (appearance).
 * Mirrors three.js Mesh class.
 * 
 * @usage
 * ```cpp
 * auto geometry = std::make_shared<BoxGeometry>(1, 1, 1);
 * auto material = std::make_shared<MeshPhongMaterial>();
 * auto mesh = std::make_shared<Mesh>(geometry, material);
 * scene->Add(mesh);
 * ```
 */

#include "object3d.h"
#include "geometry.h"
#include "material.h"
#include <memory>

namespace threecpp {

class Mesh : public Object3D {
public:
    using Ptr = std::shared_ptr<Mesh>;
    
    /**
     * @property geometry
     * @brief Geometry (shape) of the mesh
     */
    Geometry::Ptr geometry;
    
    /**
     * @property material
     * @brief Material (appearance) of the mesh
     */
    Material::Ptr material;
    
    /**
     * @method Mesh
     * @brief Constructor
     * 
     * @params
     *   - geometry (Geometry::Ptr): Shape to render
     *   - material (Material::Ptr): Surface appearance
     */
    Mesh(Geometry::Ptr geometry = nullptr, Material::Ptr material = nullptr);
    
    ~Mesh() override = default;
    
    /**
     * @method GetBoundingBox
     * @brief Get world-space bounding box
     */
    void GetBoundingBox(Vector3& min_out, Vector3& max_out) const;
    
    const char* GetTypeName() const override {
        return "Mesh";
    }
    
    std::string ToString() const override;
};

} // namespace threecpp
