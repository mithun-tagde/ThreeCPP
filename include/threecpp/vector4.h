#pragma once
/**
 * @class Vector4
 * @brief 4D vector for homogeneous coordinates and RGBA colors
 * 
 * @details
 * Used for:
 * - Homogeneous coordinates in projective geometry
 * - RGBA color values (in some contexts)
 * - Quaternion representation
 * - Generic 4D data
 * 
 * @performance O(1) for all operations
 */

#include <glm/glm.hpp>
#include <cmath>
#include <string>

namespace threecpp {

class Vector4 {
public:
    float x, y, z, w;
    
    explicit Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) noexcept
        : x(x), y(y), z(z), w(w) {}
    
    explicit Vector4(const glm::vec4& v) noexcept
        : x(v.x), y(v.y), z(v.z), w(v.w) {}
    
    operator glm::vec4() const noexcept {
        return glm::vec4(x, y, z, w);
    }
    
    Vector4 operator+(const Vector4& other) const noexcept {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    
    Vector4& operator+=(const Vector4& other) noexcept {
        x += other.x; y += other.y; z += other.z; w += other.w;
        return *this;
    }
    
    Vector4 operator-(const Vector4& other) const noexcept {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    
    Vector4& operator-=(const Vector4& other) noexcept {
        x -= other.x; y -= other.y; z -= other.z; w -= other.w;
        return *this;
    }
    
    Vector4 operator*(float scalar) const noexcept {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }
    
    friend Vector4 operator*(float scalar, const Vector4& v) noexcept {
        return v * scalar;
    }
    
    Vector4& operator*=(float scalar) noexcept {
        x *= scalar; y *= scalar; z *= scalar; w *= scalar;
        return *this;
    }
    
    Vector4 operator/(float scalar) const noexcept {
        float inv = 1.0f / scalar;
        return Vector4(x * inv, y * inv, z * inv, w * inv);
    }
    
    Vector4& operator/=(float scalar) noexcept {
        float inv = 1.0f / scalar;
        x *= inv; y *= inv; z *= inv; w *= inv;
        return *this;
    }
    
    float Dot(const Vector4& other) const noexcept {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    
    float Length() const noexcept {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }
    
    float LengthSquared() const noexcept {
        return x * x + y * y + z * z + w * w;
    }
    
    void Normalize() noexcept {
        float len = Length();
        if (len > 0.0f) {
            float inv = 1.0f / len;
            x *= inv; y *= inv; z *= inv; w *= inv;
        }
    }
    
    Vector4 Normalized() const noexcept {
        Vector4 result(*this);
        result.Normalize();
        return result;
    }
    
    bool operator==(const Vector4& other) const noexcept {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }
    
    bool operator!=(const Vector4& other) const noexcept {
        return !(*this == other);
    }
    
    float operator[](int index) const noexcept {
        return (&x)[index];
    }
    
    float& operator[](int index) noexcept {
        return (&x)[index];
    }
    
    static Vector4 Zero() noexcept { return Vector4(0, 0, 0, 0); }
    static Vector4 One() noexcept { return Vector4(1, 1, 1, 1); }
    
    std::string ToString() const;
};

} // namespace threecpp
