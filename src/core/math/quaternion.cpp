#include "../../include/threecpp/quaternion.h"
#include "../../include/threecpp/vector3.h"
#include "../../include/threecpp/matrix4.h"
#include "../../include/threecpp/euler.h"
#include <sstream>
#include <glm/gtx/quaternion.hpp>

namespace threecpp {

Quaternion Quaternion::operator*(const Quaternion& other) const noexcept {
    auto q1 = glm::quat(w, x, y, z);
    auto q2 = glm::quat(other.w, other.x, other.y, other.z);
    auto result = q1 * q2;
    return Quaternion(result.x, result.y, result.z, result.w);
}

Quaternion Quaternion::Inverse() const noexcept {
    auto q = glm::quat(w, x, y, z);
    auto inv = glm::inverse(q);
    return Quaternion(inv.x, inv.y, inv.z, inv.w);
}

Vector3 Quaternion::RotateVector(const Vector3& v) const noexcept {
    auto q = glm::quat(w, x, y, z);
    auto v_rot = glm::rotate(q, glm::vec3(v.x, v.y, v.z));
    return Vector3(v_rot.x, v_rot.y, v_rot.z);
}

Quaternion Quaternion::Slerp(const Quaternion& other, float t) const noexcept {
    auto q1 = glm::quat(w, x, y, z);
    auto q2 = glm::quat(other.w, other.x, other.y, other.z);
    
    // Ensure shortest path
    if (glm::dot(q1, q2) < 0.0f) {
        q2 = -q2;
    }
    
    auto result = glm::slerp(q1, q2, t);
    return Quaternion(result.x, result.y, result.z, result.w);
}

Quaternion Quaternion::Lerp(const Quaternion& other, float t) const noexcept {
    auto q1 = glm::quat(w, x, y, z);
    auto q2 = glm::quat(other.w, other.x, other.y, other.z);
    auto result = glm::lerp(q1, q2, t);
    return Quaternion(result.x, result.y, result.z, result.w);
}

Quaternion Quaternion::AxisAngle(const Vector3& axis, float angle) noexcept {
    auto q = glm::angleAxis(angle, glm::vec3(axis.x, axis.y, axis.z));
    return Quaternion(q.x, q.y, q.z, q.w);
}

Quaternion Quaternion::EulerAngles(const Vector3& euler) noexcept {
    auto q = glm::quat(glm::vec3(euler.x, euler.y, euler.z));
    return Quaternion(q.x, q.y, q.z, q.w);
}

Quaternion Quaternion::FromMatrix(const Matrix4& m) noexcept {
    auto q = glm::quat_cast(glm::mat4(m));
    return Quaternion(q.x, q.y, q.z, q.w);
}

Quaternion Quaternion::LookRotation(const Vector3& forward, const Vector3& up) noexcept {
    glm::vec3 f = glm::normalize(glm::vec3(forward.x, forward.y, forward.z));
    glm::vec3 u = glm::normalize(glm::vec3(up.x, up.y, up.z));
    glm::vec3 r = glm::cross(u, f);
    u = glm::cross(f, r);
    
    auto mat = glm::mat4(
        glm::vec4(r, 0),
        glm::vec4(u, 0),
        glm::vec4(-f, 0),
        glm::vec4(0, 0, 0, 1)
    );
    
    auto q = glm::quat_cast(mat);
    return Quaternion(q.x, q.y, q.z, q.w);
}

bool Quaternion::operator==(const Quaternion& other) const noexcept {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Quaternion::operator!=(const Quaternion& other) const noexcept {
    return !(*this == other);
}

std::string Quaternion::ToString() const {
    std::ostringstream oss;
    oss << "Quaternion(" << x << ", " << y << ", " << z << ", " << w << ")";
    return oss.str();
}

} // namespace threecpp
