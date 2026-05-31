#include "../../include/threecpp/object3d.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <uuid/uuid.h>

namespace threecpp {

static std::string GenerateUUID() {
    // Simple UUID-like string generation (replace with real UUID library if needed)
    static uint64_t counter = 0;
    std::ostringstream oss;
    oss << "threecpp-obj-" << counter++;
    return oss.str();
}

Object3D::Object3D()
    : uuid(GenerateUUID()) {
}

void Object3D::UpdateMatrix() {
    if (!matrix_auto_update) return;
    
    // Compute local transformation matrix: T * R * S
    Matrix4 translate = Matrix4::Translate(position);
    Matrix4 rotate = Matrix4::Rotate(quaternion);
    Matrix4 scale_mat = Matrix4::Scale(scale);
    
    m_local_matrix = translate * rotate * scale_mat;
    m_world_matrix_needs_update = true;
    
    OnMatrixChanged();
}

void Object3D::UpdateMatrixWorld(bool force) {
    if (matrix_auto_update) {
        UpdateMatrix();
    }
    
    if (force || m_world_matrix_needs_update) {
        if (auto parent_ptr = parent.lock()) {
            m_world_matrix = parent_ptr->GetWorldMatrix() * m_local_matrix;
        } else {
            m_world_matrix = m_local_matrix;
        }
        m_world_matrix_needs_update = false;
    }
    
    // Update children
    for (auto& child : children) {
        child->UpdateMatrixWorld(force);
    }
}

Vector3 Object3D::GetWorldPosition() const {
    Vector3 result;
    result.x = m_world_matrix.data[3][0];
    result.y = m_world_matrix.data[3][1];
    result.z = m_world_matrix.data[3][2];
    return result;
}

Quaternion Object3D::GetWorldQuaternion() const {
    // Extract rotation from world matrix
    return Quaternion::FromMatrix(m_world_matrix);
}

Vector3 Object3D::GetWorldScale() const {
    Vector3 scale_x(m_world_matrix.data[0][0], m_world_matrix.data[0][1], m_world_matrix.data[0][2]);
    Vector3 scale_y(m_world_matrix.data[1][0], m_world_matrix.data[1][1], m_world_matrix.data[1][2]);
    Vector3 scale_z(m_world_matrix.data[2][0], m_world_matrix.data[2][1], m_world_matrix.data[2][2]);
    
    return Vector3(scale_x.Length(), scale_y.Length(), scale_z.Length());
}

void Object3D::LookAt(const Vector3& target, const Vector3& up) {
    Vector3 world_pos = GetWorldPosition();
    Matrix4 view = Matrix4::LookAt(world_pos, target, up);
    
    // Extract rotation from view matrix
    quaternion = Quaternion::FromMatrix(view);
    UpdateMatrix();
}

void Object3D::Traverse(std::function<void(Object3D*)> callback) {
    callback(this);
    for (auto& child : children) {
        child->Traverse(callback);
    }
}

void Object3D::TraverseVisible(std::function<void(Object3D*)> callback) {
    if (!visible) return;
    
    callback(this);
    for (auto& child : children) {
        child->TraverseVisible(callback);
    }
}

Object3D::Ptr Object3D::GetObjectByName(const std::string& target_name) {
    if (name == target_name) {
        return shared_from_this();
    }
    
    for (auto& child : children) {
        auto result = child->GetObjectByName(target_name);
        if (result) return result;
    }
    
    return nullptr;
}

Object3D::Ptr Object3D::GetObjectById(uint32_t target_id) {
    // Note: This is a placeholder. Real implementation would need a numeric ID.
    return nullptr;
}

Vector3 Object3D::GetFront() const {
    // Front is typically -Z axis
    Vector3 front(0, 0, -1);
    return quaternion.RotateVector(front).Normalized();
}

Vector3 Object3D::GetRight() const {
    Vector3 right(1, 0, 0);
    return quaternion.RotateVector(right).Normalized();
}

Vector3 Object3D::GetUp() const {
    Vector3 up(0, 1, 0);
    return quaternion.RotateVector(up).Normalized();
}

Object3D::Ptr Object3D::Clone(bool recursive) {
    auto clone = std::make_shared<Object3D>();
    clone->position = position;
    clone->quaternion = quaternion;
    clone->scale = scale;
    clone->visible = visible;
    clone->name = name;
    clone->user_data = user_data;
    
    if (recursive) {
        for (const auto& child : children) {
            clone->Add(child->Clone(true));
        }
    }
    
    return clone;
}

std::string Object3D::ToString() const {
    std::ostringstream oss;
    oss << "Object3D(\"" << name << "\", children=" << children.size() << ")";
    return oss.str();
}

} // namespace threecpp
