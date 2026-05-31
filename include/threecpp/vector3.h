#pragma once
/**
 * @class Vector3
 * @brief 3D vector for positions, directions, and scales
 * 
 * @details
 * Represents a 3-dimensional vector commonly used for:
 * - Object positions in 3D space
 * - Direction vectors (normals, light direction)
 * - Velocity and acceleration
 * - Scaling factors
 * 
 * All operations maintain mathematical correctness:
 * - Addition: component-wise sum
 * - Multiplication: scalar or dot/cross product
 * - Normalization: unit vector in same direction
 * 
 * @performance O(1) for all operations
 * @thread_safe Copy and move are thread-safe
 */

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <cmath>
#include <string>

namespace threecpp {

class Vector3 {
public:
    float x, y, z;
    
    /**
     * @method Vector3
     * @brief Default constructor
     * 
     * @params
     *   - x (float): X component. Default: 0
     *   - y (float): Y component. Default: 0
     *   - z (float): Z component. Default: 0
     * 
     * @returns
     *   Vector3 instance with specified components
     * 
     * @example
     * ```cpp
     * Vector3 zero;                    // (0, 0, 0)
     * Vector3 pos(1.5f, 2.0f, 3.5f);  // (1.5, 2, 3.5)
     * ```
     */
    explicit Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) noexcept
        : x(x), y(y), z(z) {}
    
    /**
     * @method Vector3 (from glm)
     * @brief Conversion constructor from GLM vector
     * 
     * @params
     *   - v (const glm::vec3&): GLM vector to convert from
     * 
     * @returns
     *   Vector3 with same components as glm::vec3
     */
    explicit Vector3(const glm::vec3& v) noexcept
        : x(v.x), y(v.y), z(v.z) {}
    
    // Conversion to GLM
    operator glm::vec3() const noexcept {
        return glm::vec3(x, y, z);
    }
    
    /**
     * @method operator+
     * @brief Vector addition
     * 
     * @params
     *   - other (const Vector3&): Vector to add
     * 
     * @returns
     *   New Vector3 containing component-wise sum
     * 
     * @example
     * ```cpp
     * Vector3 a(1, 2, 3);
     * Vector3 b(4, 5, 6);
     * Vector3 c = a + b;  // (5, 7, 9)
     * ```
     */
    Vector3 operator+(const Vector3& other) const noexcept {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3& operator+=(const Vector3& other) noexcept {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    
    /**
     * @method operator-
     * @brief Vector subtraction
     * 
     * @params
     *   - other (const Vector3&): Vector to subtract
     * 
     * @returns
     *   New Vector3 containing component-wise difference
     */
    Vector3 operator-(const Vector3& other) const noexcept {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    
    Vector3& operator-=(const Vector3& other) noexcept {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    
    /**
     * @method operator*
     * @brief Scalar multiplication
     * 
     * @params
     *   - scalar (float): Factor to scale by
     * 
     * @returns
     *   New Vector3 with components scaled
     */
    Vector3 operator*(float scalar) const noexcept {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    
    friend Vector3 operator*(float scalar, const Vector3& v) noexcept {
        return v * scalar;
    }
    
    Vector3& operator*=(float scalar) noexcept {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    
    /**
     * @method operator/
     * @brief Scalar division
     * 
     * @params
     *   - scalar (float): Divisor (must be non-zero)
     * 
     * @returns
     *   New Vector3 with components divided
     */
    Vector3 operator/(float scalar) const noexcept {
        float inv = 1.0f / scalar;
        return Vector3(x * inv, y * inv, z * inv);
    }
    
    Vector3& operator/=(float scalar) noexcept {
        float inv = 1.0f / scalar;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }
    
    /**
     * @method Dot
     * @brief Scalar (dot) product
     * 
     * @params
     *   - other (const Vector3&): Vector to dot with
     * 
     * @returns
     *   (float) Dot product: a·b = ax*bx + ay*by + az*bz
     * 
     * @notes
     *   - Result is 0 if vectors are perpendicular
     *   - Result is positive if angle < 90°
     *   - Result is negative if angle > 90°
     */
    float Dot(const Vector3& other) const noexcept {
        return x * other.x + y * other.y + z * other.z;
    }
    
    /**
     * @method Cross
     * @brief Vector (cross) product
     * 
     * @params
     *   - other (const Vector3&): Vector to cross with
     * 
     * @returns
     *   New Vector3 perpendicular to both input vectors
     * 
     * @notes
     *   - Right-hand rule applies
     *   - Length = |a| * |b| * sin(angle)
     *   - Order matters: a × b = -(b × a)
     */
    Vector3 Cross(const Vector3& other) const noexcept {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    /**
     * @method Length
     * @brief Magnitude (Euclidean norm)
     * 
     * @params (none)
     * 
     * @returns
     *   (float) sqrt(x² + y² + z²)
     * 
     * @example
     * ```cpp
     * Vector3 v(3, 4, 0);
     * float len = v.Length();  // 5.0
     * ```
     */
    float Length() const noexcept {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    /**
     * @method LengthSquared
     * @brief Squared magnitude (faster, no sqrt)
     * 
     * @params (none)
     * 
     * @returns
     *   (float) x² + y² + z²
     * 
     * @notes
     *   Use this for comparisons instead of Length() for performance
     */
    float LengthSquared() const noexcept {
        return x * x + y * y + z * z;
    }
    
    /**
     * @method Normalize
     * @brief Convert to unit vector (modifies in place)
     * 
     * @params (none)
     * 
     * @returns (void)
     * 
     * @notes
     *   - Modifies this vector
     *   - Zero vectors are left unchanged
     */
    void Normalize() noexcept {
        float len = Length();
        if (len > 0.0f) {
            float inv = 1.0f / len;
            x *= inv;
            y *= inv;
            z *= inv;
        }
    }
    
    /**
     * @method Normalized
     * @brief Get unit vector copy (doesn't modify)
     * 
     * @params (none)
     * 
     * @returns
     *   New Vector3 with Length() == 1.0
     */
    Vector3 Normalized() const noexcept {
        Vector3 result(*this);
        result.Normalize();
        return result;
    }
    
    /**
     * @method Distance
     * @brief Distance to another vector
     * 
     * @params
     *   - other (const Vector3&): Target vector
     * 
     * @returns
     *   (float) Euclidean distance
     */
    float Distance(const Vector3& other) const noexcept {
        return (*this - other).Length();
    }
    
    /**
     * @method DistanceSquared
     * @brief Squared distance (faster, no sqrt)
     * 
     * @params
     *   - other (const Vector3&): Target vector
     * 
     * @returns
     *   (float) Squared distance
     */
    float DistanceSquared(const Vector3& other) const noexcept {
        return (*this - other).LengthSquared();
    }
    
    /**
     * @method Angle
     * @brief Angle between vectors in radians
     * 
     * @params
     *   - other (const Vector3&): Other vector
     * 
     * @returns
     *   (float) Angle in radians [0, π]
     */
    float Angle(const Vector3& other) const noexcept {
        float len_a = Length();
        float len_b = other.Length();
        if (len_a == 0.0f || len_b == 0.0f) return 0.0f;
        
        float cos_angle = Dot(other) / (len_a * len_b);
        // Clamp to [-1, 1] to handle floating point errors
        cos_angle = (cos_angle > 1.0f) ? 1.0f : (cos_angle < -1.0f) ? -1.0f : cos_angle;
        return std::acos(cos_angle);
    }
    
    /**
     * @method Lerp
     * @brief Linear interpolation between vectors
     * 
     * @params
     *   - other (const Vector3&): Target vector
     *   - t (float): Blend factor [0, 1]. 0=this, 1=other
     * 
     * @returns
     *   New Vector3 interpolated between this and other
     */
    Vector3 Lerp(const Vector3& other, float t) const noexcept {
        return *this + (other - *this) * t;
    }
    
    // Comparison operators
    bool operator==(const Vector3& other) const noexcept {
        return x == other.x && y == other.y && z == other.z;
    }
    
    bool operator!=(const Vector3& other) const noexcept {
        return !(*this == other);
    }
    
    // Element access
    float operator[](int index) const noexcept {
        return (&x)[index];
    }
    
    float& operator[](int index) noexcept {
        return (&x)[index];
    }
    
    // Static convenience vectors
    static Vector3 Zero() noexcept { return Vector3(0, 0, 0); }
    static Vector3 One() noexcept { return Vector3(1, 1, 1); }
    static Vector3 Forward() noexcept { return Vector3(0, 0, 1); }
    static Vector3 Back() noexcept { return Vector3(0, 0, -1); }
    static Vector3 Up() noexcept { return Vector3(0, 1, 0); }
    static Vector3 Down() noexcept { return Vector3(0, -1, 0); }
    static Vector3 Right() noexcept { return Vector3(1, 0, 0); }
    static Vector3 Left() noexcept { return Vector3(-1, 0, 0); }
    
    // String conversion (for debugging)
    std::string ToString() const;
};

} // namespace threecpp
