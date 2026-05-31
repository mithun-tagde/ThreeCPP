#pragma once
/**
 * @class Euler
 * @brief Euler angles for rotations (pitch, yaw, roll)
 * 
 * @details
 * Represents rotations using three angles.
 * Disadvantages vs Quaternion:
 * - Can suffer from gimbal lock
 * - Less smooth interpolation
 * 
 * Advantages:
 * - More intuitive for many users
 * - Easier to debug
 * 
 * Order: YXZ (Yaw, Pitch, Roll) - common in 3D graphics
 */

#include <glm/glm.hpp>
#include <cmath>
#include <string>

namespace threecpp {

class Vector3;
class Quaternion;

class Euler {
public:
    float x, y, z;  // pitch, yaw, roll
    
    enum class RotationOrder {
        XYZ,
        YXZ,  // Default - common in 3D graphics
        ZXY,
        ZYX,
        YZX,
        XZY
    };
    
    RotationOrder order = RotationOrder::YXZ;
    
    /**
     * @method Euler
     * @brief Default constructor
     * 
     * @params
     *   - x, y, z (float): Rotation angles in radians (pitch, yaw, roll)
     */
    explicit Euler(float x = 0.0f, float y = 0.0f, float z = 0.0f, 
                   RotationOrder order = RotationOrder::YXZ) noexcept
        : x(x), y(y), z(z), order(order) {}
    
    /**
     * @method Euler (from Vector3)
     * @brief Construct from vector
     */
    explicit Euler(const Vector3& v, RotationOrder order = RotationOrder::YXZ) noexcept;
    
    /**
     * @method SetFromQuaternion
     * @brief Set from quaternion
     * 
     * @params
     *   - q (const Quaternion&): Source quaternion
     * 
     * @returns (void)
     */
    void SetFromQuaternion(const Quaternion& q) noexcept;
    
    /**
     * @method ToQuaternion
     * @brief Convert to quaternion
     * 
     * @params (none)
     * 
     * @returns
     *   Quaternion representing same rotation
     */
    Quaternion ToQuaternion() const noexcept;
    
    // Comparison
    bool operator==(const Euler& other) const noexcept {
        return x == other.x && y == other.y && z == other.z && order == other.order;
    }
    
    bool operator!=(const Euler& other) const noexcept {
        return !(*this == other);
    }
    
    std::string ToString() const;
};

} // namespace threecpp
