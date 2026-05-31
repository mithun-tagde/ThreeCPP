#include "../../include/threecpp/color.h"
#include <sstream>
#include <map>
#include <algorithm>

namespace threecpp {

Color::Color(const std::string& name) noexcept {
    static const std::map<std::string, uint32_t> colorNames{
        {"black", 0x000000},
        {"white", 0xFFFFFF},
        {"red", 0xFF0000},
        {"green", 0x00FF00},
        {"blue", 0x0000FF},
        {"yellow", 0xFFFF00},
        {"cyan", 0x00FFFF},
        {"magenta", 0xFF00FF},
        {"gray", 0x808080},
        {"grey", 0x808080},
    };
    
    std::string lower_name = name;
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);
    
    auto it = colorNames.find(lower_name);
    if (it != colorNames.end()) {
        SetHex(it->second);
    } else if (lower_name[0] == '#' && lower_name.length() == 7) {
        // Parse hex string like "#FF0000"
        uint32_t hex = std::stoul(lower_name.substr(1), nullptr, 16);
        SetHex(hex);
    } else {
        // Default to white
        r = g = b = 1.0f;
    }
}

void Color::SetHSL(float h, float s, float l) noexcept {
    // Convert HSL to RGB
    h = std::fmod(h, 1.0f);
    if (h < 0) h += 1.0f;
    s = std::max(0.0f, std::min(1.0f, s));
    l = std::max(0.0f, std::min(1.0f, l));
    
    auto hue2rgb = [](float p, float q, float t) {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1.0f / 6.0f) return p + (q - p) * 6 * t;
        if (t < 1.0f / 2.0f) return q;
        if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6;
        return p;
    };
    
    float q = l < 0.5f ? l * (1 + s) : l + s - l * s;
    float p = 2 * l - q;
    
    r = hue2rgb(p, q, h + 1.0f / 3.0f);
    g = hue2rgb(p, q, h);
    b = hue2rgb(p, q, h - 1.0f / 3.0f);
}

std::string Color::ToString() const {
    std::ostringstream oss;
    oss << "Color(#" << std::hex << GetHex() << ")";
    return oss.str();
}

} // namespace threecpp
