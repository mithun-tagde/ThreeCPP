#pragma once
/**
 * @class Quaternion
 * @brief Quaternion for smooth 3D rotations
 * 
 * @details
 * Represents rotation using 4 components (x, y, z, w).
 * Advantages over Euler angles:
 * - No gimbal lock
 * - Smooth interpolation
 * - More efficient for animation
 * 
 * Format: q = w + xi + yj + zk
 * Or: q = (w, x, y, z) where w is the scalar part
 * 
 * @performance O(1) for most operations
 * @thread_safe Copy and move are thread-safe
 */

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cmath>
#include <string>

namespace threecpp {

class Vector3;
class Matrix4;

class Quaternion {
public:
    float x, y, z, w;
    
    /**
     * @method Quaternion
     * @brief Default constructor - identity rotation
     * 
     * @params
     *   - x, y, z, w (float): Quaternion components
     */
    explicit Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) noexcept
        : x(x), y(y), z(z), w(w) {}
    
    /**
     * @method Quaternion
     * @brief From GLM quaternion
     * 
     * @params
     *   - q (const glm::quat&): GLM quaternion
     */
    explicit Quaternion(const glm::quat& q) noexcept
        : x(q.x), y(q.y), z(q.z), w(q.w) {}
    
    operator glm::quat() const noexcept {
        return glm::quat(w, x, y, z);
    }
    
    /**
     * @method operator*
     * @brief Quaternion multiplication (composition of rotations)
     * 
     * @params
     *   - other (const Quaternion&): Second rotation
     * 
     * @returns
     *   New quaternion representing combined rotation
     * 
     * @notes
     *   - Order matters: q1 * q2 ≠ q2 * q1
     */
    Quaternion operator*(const Quaternion& other) const noexcept;
    
    Quaternion& operator*=(const Quaternion& other) noexcept {
        *this = *this * other;
        return *this;
    }
    
    /**
     * @method Conjugate
     * @brief Get conjugate (inverse for unit quaternions)
     * 
     * @params (none)
     * 
     * @returns
     *   Quaternion(−x, −y, −z, w)
     */
    Quaternion Conjugate() const noexcept {
        return Quaternion(-x, -y, -z, w);
    }
    
    /**
     * @method Inverse
     * @brief Get inverse rotation
     * 
     * @params (none)
     * 
     * @returns
     *   Quaternion that undoes this rotation
     */
    Quaternion Inverse() const noexcept;
    
    /**
     * @method Length
     * @brief Magnitude of quaternion
     * 
     * @params (none)
     * 
     * @returns
     *   (float) sqrt(x² + y² + z² + w²)
     * 
     * @notes
     *   Should be 1.0 for unit quaternions (most common)
     */
    float Length() const noexcept {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }
    
    /**
     * @method LengthSquared
     * @brief Squared magnitude
     * 
     * @params (none)
     * 
     * @returns
     *   (float) x² + y² + z² + w²
     */
    float LengthSquared() const noexcept {
        return x * x + y * y + z * z + w * w;
    }
    
    /**
     * @method Normalize
     * @brief Convert to unit quaternion (modifies in place)
     * 
     * @params (none)
     * 
     * @returns (void)
     * 
     * @notes
     *   Most rotation operations require unit quaternions
     */
    void Normalize() noexcept {
        float len = Length();
        if (len > 0.0f) {
            float inv = 1.0f / len;
            x *= inv; y *= inv; z *= inv; w *= inv;
        }
    }
    
    /**
     * @method Normalized
     * @brief Get unit quaternion copy
     * 
     * @params (none)
     * 
     * @returns
     *   New normalized quaternion
     */
    Quaternion Normalized() const noexcept {
        Quaternion result(*this);
        result.Normalize();
        return result;
    }
    
    /**
     * @method Dot
     * @brief Dot product with another quaternion
     * 
     * @params
     *   - other (const Quaternion&): Other quaternion
     * 
     * @returns
     *   (float) x1*x2 + y1*y2 + z1*z2 + w1*w2
     */
    float Dot(const Quaternion& other) const noexcept {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    
    /**
     * @method RotateVector
     * @brief Rotate a vector by this quaternion
     * 
     * @params
     *   - v (const Vector3&): Vector to rotate
     * 
     * @returns
     *   New rotated vector
     */
    Vector3 RotateVector(const Vector3& v) const noexcept;
    
    /**
     * @method Slerp
     * @brief Spherical linear interpolation
     * 
     * @params
     *   - other (const Quaternion&): Target quaternion
     *   - t (float): Blend factor [0, 1]. 0=this, 1=other
     * 
     * @returns
     *   New quaternion smoothly interpolated
     * 
     * @notes
     *   - Produces smooth rotation animation
     *   - Better than Lerp for rotations
     */
    Quaternion Slerp(const Quaternion& other, float t) const noexcept;
    
    /**
     * @method Lerp
     * @brief Linear interpolation (faster but less smooth than Slerp)
     * 
     * @params
     *   - other (const Quaternion&): Target quaternion
     *   - t (float): Blend factor [0, 1]
     * 
     * @returns
     *   New quaternion interpolated (should be normalized after)
     */
    Quaternion Lerp(const Quaternion& other, float t) const noexcept;
    
    // Static constructors
    
    /**
     * @method AxisAngle
     * @brief Create quaternion from axis and angle
     * 
     * @params
     *   - axis (const Vector3&): Rotation axis (normalized)
     *   - angle (float): Rotation angle in radians
     * 
     * @returns
     *   New quaternion representing this rotation
     */
    static Quaternion AxisAngle(const Vector3& axis, float angle) noexcept;
    
    /**
     * @method EulerAngles
     * @brief Create quaternion from Euler angles
     * 
     * @params
     *   - euler (const Vector3&): Rotation in radians (pitch, yaw, roll)
     * 
     * @returns
     *   New quaternion
     * 
     * @notes
     *   Uses YXZ convention (Yaw, Pitch, Roll)
     */
    static Quaternion EulerAngles(const Vector3& euler) noexcept;
    
    /**
     * @method FromMatrix
     * @brief Create quaternion from rotation matrix
     * 
     * @params
     *   - m (const Matrix4&): Rotation matrix
     * 
     * @returns
     *   New quaternion
     */
    static Quaternion FromMatrix(const Matrix4& m) noexcept;
    
    /**
     * @method LookRotation
     * @brief Create quaternion that rotates from one direction to another
     * 
     * @params
     *   - forward (const Vector3&): Target forward direction
     *   - up (const Vector3&): Up direction (default: +Y)
     * 
     * @returns
     *   New quaternion
     */
    static Quaternion LookRotation(const Vector3& forward, const Vector3& up = Vector3::Up()) noexcept;
    
    bool operator==(const Quaternion& other) const noexcept;
    bool operator!=(const Quaternion& other) const noexcept;
    
    /**
     * @method Identity
     * @brief Get identity rotation (no rotation)
     * 
     * @params (none)
     * 
     * @returns
     *   Quaternion(0, 0, 0, 1)
     */
    static Quaternion Identity() noexcept {
        return Quaternion(0, 0, 0, 1);
    }
    
    std::string ToString() const;
};

} // namespace threecpp
