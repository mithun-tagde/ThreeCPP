#pragma once
/**
 * @class Color
 * @brief RGB color representation
 * 
 * @details
 * Represents colors with red, green, blue components.
 * Components are typically in range [0, 1] but can exceed for HDR.
 * 
 * Can be constructed from:
 * - RGB floats: Color(0.5f, 0.5f, 0.5f)
 * - 24-bit hex: Color(0xFF0000) for red
 * - Color names: Color("red")
 */

#include <glm/glm.hpp>
#include <cstdint>
#include <string>

namespace threecpp {

class Color {
public:
    float r, g, b;
    
    /**
     * @method Color
     * @brief Default constructor - white
     * 
     * @params
     *   - r, g, b (float): RGB components [0, 1]. Default: 1
     */
    explicit Color(float r = 1.0f, float g = 1.0f, float b = 1.0f) noexcept
        : r(r), g(g), b(b) {}
    
    /**
     * @method Color (from hex)
     * @brief Construct from 24-bit hex color
     * 
     * @params
     *   - hex (uint32_t): Color as 0xRRGGBB
     * 
     * @example
     * ```cpp
     * Color red(0xFF0000);    // Red
     * Color green(0x00FF00);  // Green
     * Color blue(0x0000FF);   // Blue
     * ```
     */
    explicit Color(uint32_t hex) noexcept {
        SetHex(hex);
    }
    
    /**
     * @method Color (from string)
     * @brief Construct from color name or hex string
     * 
     * @params
     *   - name (const std::string&): Color name or "#RRGGBB"
     * 
     * @example
     * ```cpp
     * Color red("red");
     * Color blue("#0000FF");
     * ```
     */
    explicit Color(const std::string& name) noexcept;
    
    explicit Color(const glm::vec3& v) noexcept
        : r(v.r), g(v.g), b(v.b) {}
    
    operator glm::vec3() const noexcept {
        return glm::vec3(r, g, b);
    }
    
    /**
     * @method SetHex
     * @brief Set color from hex value
     * 
     * @params
     *   - hex (uint32_t): Color as 0xRRGGBB
     * 
     * @returns (void)
     */
    void SetHex(uint32_t hex) noexcept {
        r = ((hex >> 16) & 255) / 255.0f;
        g = ((hex >> 8) & 255) / 255.0f;
        b = (hex & 255) / 255.0f;
    }
    
    /**
     * @method GetHex
     * @brief Get color as hex value
     * 
     * @params (none)
     * 
     * @returns
     *   (uint32_t) Color as 0xRRGGBB
     */
    uint32_t GetHex() const noexcept {
        uint32_t rr = static_cast<uint32_t>(r * 255) & 255;
        uint32_t gg = static_cast<uint32_t>(g * 255) & 255;
        uint32_t bb = static_cast<uint32_t>(b * 255) & 255;
        return (rr << 16) | (gg << 8) | bb;
    }
    
    /**
     * @method SetHSL
     * @brief Set color from HSL values
     * 
     * @params
     *   - h, s, l (float): Hue [0, 1], Saturation [0, 1], Lightness [0, 1]
     * 
     * @returns (void)
     */
    void SetHSL(float h, float s, float l) noexcept;
    
    /**
     * @method GetBrightness
     * @brief Get perceived brightness
     * 
     * @params (none)
     * 
     * @returns
     *   (float) Brightness in range [0, 1]
     */
    float GetBrightness() const noexcept {
        return (r * 0.299f + g * 0.587f + b * 0.114f);
    }
    
    // Operators
    Color operator+(const Color& other) const noexcept {
        return Color(r + other.r, g + other.g, b + other.b);
    }
    
    Color& operator+=(const Color& other) noexcept {
        r += other.r; g += other.g; b += other.b;
        return *this;
    }
    
    Color operator*(float scalar) const noexcept {
        return Color(r * scalar, g * scalar, b * scalar);
    }
    
    friend Color operator*(float scalar, const Color& c) noexcept {
        return c * scalar;
    }
    
    Color& operator*=(float scalar) noexcept {
        r *= scalar; g *= scalar; b *= scalar;
        return *this;
    }
    
    /**
     * @method Lerp
     * @brief Linear interpolation between colors
     * 
     * @params
     *   - other (const Color&): Target color
     *   - t (float): Blend factor [0, 1]
     * 
     * @returns
     *   New color interpolated
     */
    Color Lerp(const Color& other, float t) const noexcept {
        return Color(
            r + (other.r - r) * t,
            g + (other.g - g) * t,
            b + (other.b - b) * t
        );
    }
    
    bool operator==(const Color& other) const noexcept {
        return r == other.r && g == other.g && b == other.b;
    }
    
    bool operator!=(const Color& other) const noexcept {
        return !(*this == other);
    }
    
    // Static color constants
    static Color Black() noexcept { return Color(0, 0, 0); }
    static Color White() noexcept { return Color(1, 1, 1); }
    static Color Red() noexcept { return Color(1, 0, 0); }
    static Color Green() noexcept { return Color(0, 1, 0); }
    static Color Blue() noexcept { return Color(0, 0, 1); }
    static Color Yellow() noexcept { return Color(1, 1, 0); }
    static Color Cyan() noexcept { return Color(0, 1, 1); }
    static Color Magenta() noexcept { return Color(1, 0, 1); }
    static Color Gray() noexcept { return Color(0.5f, 0.5f, 0.5f); }
    
    std::string ToString() const;
};

} // namespace threecpp
