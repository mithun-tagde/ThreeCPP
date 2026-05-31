#pragma once
/**
 * @class Geometry
 * @brief Base class for geometries
 * 
 * @details
 * Abstract base class for all geometry types.
 * Defines vertices, faces, normals, UVs.
 */

#include <memory>
#include <vector>
#include "vector3.h"
#include "vector2.h"

namespace threecpp {

class Geometry {
public:
    using Ptr = std::shared_ptr<Geometry>;
    
    /**
     * @property vertices
     * @brief Vertex positions
     */
    std::vector<Vector3> vertices;
    
    /**
     * @property normals
     * @brief Vertex normals (for lighting)
     */
    std::vector<Vector3> normals;
    
    /**
     * @property uvs
     * @brief Texture coordinates
     */
    std::vector<Vector2> uvs;
    
    /**
     * @property faces
     * @brief Triangle face indices [i0, i1, i2, ...]
     */
    std::vector<uint32_t> faces;
    
    virtual ~Geometry() = default;
    
    /**
     * @method ComputeNormals
     * @brief Auto-calculate vertex normals
     */
    void ComputeNormals();
    
    /**
     * @method GetBoundingBox
     * @brief Get bounding box min/max corners
     */
    void GetBoundingBox(Vector3& min_out, Vector3& max_out) const;
};

} // namespace threecpp
