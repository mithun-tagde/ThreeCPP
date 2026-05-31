#include "../../include/threecpp/euler.h"
#include "../../include/threecpp/vector3.h"
#include "../../include/threecpp/quaternion.h"
#include <sstream>
#include <glm/gtc/quaternion.hpp>

namespace threecpp {

Euler::Euler(const Vector3& v, RotationOrder order) noexcept
    : x(v.x), y(v.y), z(v.z), order(order) {}

void Euler::SetFromQuaternion(const Quaternion& q) noexcept {
    auto glm_q = glm::quat(q.w, q.x, q.y, q.z);
    auto euler = glm::eulerAngles(glm_q);
    x = euler.x;
    y = euler.y;
    z = euler.z;
}

Quaternion Euler::ToQuaternion() const noexcept {
    auto q = glm::quat(glm::vec3(x, y, z));
    return Quaternion(q.x, q.y, q.z, q.w);
}

std::string Euler::ToString() const {
    std::ostringstream oss;
    oss << "Euler(" << x << ", " << y << ", " << z << ")";
    return oss.str();
}

} // namespace threecpp
