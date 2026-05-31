#include "../../include/threecpp/matrix4.h"
#include "../../include/threecpp/vector3.h"
#include "../../include/threecpp/quaternion.h"
#include <sstream>

namespace threecpp {

Matrix4 Matrix4::Translate(const Vector3& offset) noexcept {
    return Matrix4(glm::translate(glm::mat4(1.0f), glm::vec3(offset.x, offset.y, offset.z)));
}

Matrix4 Matrix4::Scale(const Vector3& scale) noexcept {
    return Matrix4(glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z)));
}

Matrix4 Matrix4::RotateX(float angle) noexcept {
    return Matrix4(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1, 0, 0)));
}

Matrix4 Matrix4::RotateY(float angle) noexcept {
    return Matrix4(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)));
}

Matrix4 Matrix4::RotateZ(float angle) noexcept {
    return Matrix4(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1)));
}

Matrix4 Matrix4::Rotate(const Quaternion& q) noexcept {
    return Matrix4(glm::mat4_cast(glm::quat(q.w, q.x, q.y, q.z)));
}

Matrix4 Matrix4::Perspective(float fovy, float aspect, float znear, float zfar) noexcept {
    return Matrix4(glm::perspective(fovy, aspect, znear, zfar));
}

Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, 
                              float znear, float zfar) noexcept {
    return Matrix4(glm::ortho(left, right, bottom, top, znear, zfar));
}

Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) noexcept {
    return Matrix4(glm::lookAt(
        glm::vec3(eye.x, eye.y, eye.z),
        glm::vec3(center.x, center.y, center.z),
        glm::vec3(up.x, up.y, up.z)
    ));
}

bool Matrix4::operator==(const Matrix4& other) const noexcept {
    return data == other.data;
}

bool Matrix4::operator!=(const Matrix4& other) const noexcept {
    return data != other.data;
}

std::string Matrix4::ToString() const {
    std::ostringstream oss;
    oss << "Matrix4[\n";
    for (int i = 0; i < 4; i++) {
        oss << "  [" << data[0][i] << ", " << data[1][i] << ", " 
            << data[2][i] << ", " << data[3][i] << "]\n";
    }
    oss << "]";
    return oss.str();
}

} // namespace threecpp
