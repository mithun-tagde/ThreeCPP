#pragma once
/**
 * @class Vector2
 * @brief 2D vector for 2D coordinates and texture coordinates
 * 
 * @details
 * Commonly used for:
 * - 2D positions and directions
 * - Texture coordinates (UV mapping)
 * - Screen coordinates
 * 
 * @performance O(1) for all operations
 * @thread_safe Copy and move are thread-safe
 */

#include <glm/glm.hpp>
#include <cmath>
#include <string>

namespace threecpp {

class Vector2 {
public:
    float x, y;
    
    /**
     * @method Vector2
     * @brief Default constructor
     * 
     * @params
     *   - x (float): X component. Default: 0
     *   - y (float): Y component. Default: 0
     * 
     * @returns
     *   Vector2 instance
     */
    explicit Vector2(float x = 0.0f, float y = 0.0f) noexcept
        : x(x), y(y) {}
    
    explicit Vector2(const glm::vec2& v) noexcept
        : x(v.x), y(v.y) {}
    
    operator glm::vec2() const noexcept {
        return glm::vec2(x, y);
    }
    
    Vector2 operator+(const Vector2& other) const noexcept {
        return Vector2(x + other.x, y + other.y);
    }
    
    Vector2& operator+=(const Vector2& other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Vector2 operator-(const Vector2& other) const noexcept {
        return Vector2(x - other.x, y - other.y);
    }
    
    Vector2& operator-=(const Vector2& other) noexcept {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    
    Vector2 operator*(float scalar) const noexcept {
        return Vector2(x * scalar, y * scalar);
    }
    
    friend Vector2 operator*(float scalar, const Vector2& v) noexcept {
        return v * scalar;
    }
    
    Vector2& operator*=(float scalar) noexcept {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    
    Vector2 operator/(float scalar) const noexcept {
        float inv = 1.0f / scalar;
        return Vector2(x * inv, y * inv);
    }
    
    Vector2& operator/=(float scalar) noexcept {
        float inv = 1.0f / scalar;
        x *= inv;
        y *= inv;
        return *this;
    }
    
    float Dot(const Vector2& other) const noexcept {
        return x * other.x + y * other.y;
    }
    
    float Length() const noexcept {
        return std::sqrt(x * x + y * y);
    }
    
    float LengthSquared() const noexcept {
        return x * x + y * y;
    }
    
    void Normalize() noexcept {
        float len = Length();
        if (len > 0.0f) {
            float inv = 1.0f / len;
            x *= inv;
            y *= inv;
        }
    }
    
    Vector2 Normalized() const noexcept {
        Vector2 result(*this);
        result.Normalize();
        return result;
    }
    
    float Distance(const Vector2& other) const noexcept {
        return (*this - other).Length();
    }
    
    Vector2 Lerp(const Vector2& other, float t) const noexcept {
        return *this + (other - *this) * t;
    }
    
    bool operator==(const Vector2& other) const noexcept {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Vector2& other) const noexcept {
        return !(*this == other);
    }
    
    float operator[](int index) const noexcept {
        return (&x)[index];
    }
    
    float& operator[](int index) noexcept {
        return (&x)[index];
    }
    
    static Vector2 Zero() noexcept { return Vector2(0, 0); }
    static Vector2 One() noexcept { return Vector2(1, 1); }
    
    std::string ToString() const;
};

} // namespace threecpp
