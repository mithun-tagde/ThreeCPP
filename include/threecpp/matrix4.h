#pragma once
/**
 * @class Matrix4
 * @brief 4x4 transformation matrix for 3D graphics
 * 
 * @details
 * Used for:
 * - Affine transformations (translation, rotation, scale)
 * - Projection matrices (perspective, orthographic)
 * - View transformations
 * - Combined transformations
 * 
 * Stored in column-major order (GLM convention):
 * [m00 m10 m20 m30]
 * [m01 m11 m21 m31]
 * [m02 m12 m22 m32]
 * [m03 m13 m23 m33]
 * 
 * @performance O(1) for most operations, O(n³) for inversion
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <string>

namespace threecpp {

class Vector3;
class Quaternion;

class Matrix4 {
public:
    glm::mat4 data;
    
    /**
     * @method Matrix4
     * @brief Default constructor - identity matrix
     */
    Matrix4() noexcept : data(1.0f) {}
    
    /**
     * @method Matrix4
     * @brief From GLM matrix
     * 
     * @params
     *   - m (const glm::mat4&): GLM matrix
     */
    explicit Matrix4(const glm::mat4& m) noexcept : data(m) {}
    
    operator glm::mat4() const noexcept {
        return data;
    }
    
    operator glm::mat4&() noexcept {
        return data;
    }
    
    /**
     * @method operator*
     * @brief Matrix multiplication
     * 
     * @params
     *   - other (const Matrix4&): Right-hand matrix
     * 
     * @returns
     *   New Matrix4 containing product
     */
    Matrix4 operator*(const Matrix4& other) const noexcept {
        return Matrix4(data * other.data);
    }
    
    Matrix4& operator*=(const Matrix4& other) noexcept {
        data = data * other.data;
        return *this;
    }
    
    /**
     * @method Translate
     * @brief Create translation matrix
     * 
     * @params
     *   - offset (const Vector3&): Translation vector
     * 
     * @returns
     *   New translation matrix
     */
    static Matrix4 Translate(const Vector3& offset) noexcept;
    
    /**
     * @method Scale
     * @brief Create scaling matrix
     * 
     * @params
     *   - scale (const Vector3&): Scale factors
     * 
     * @returns
     *   New scaling matrix
     */
    static Matrix4 Scale(const Vector3& scale) noexcept;
    
    /**
     * @method RotateX, RotateY, RotateZ
     * @brief Create rotation matrices around axes
     * 
     * @params
     *   - angle (float): Rotation angle in radians
     * 
     * @returns
     *   New rotation matrix
     */
    static Matrix4 RotateX(float angle) noexcept;
    static Matrix4 RotateY(float angle) noexcept;
    static Matrix4 RotateZ(float angle) noexcept;
    
    /**
     * @method Rotate
     * @brief Create rotation matrix from quaternion
     * 
     * @params
     *   - q (const Quaternion&): Rotation quaternion
     * 
     * @returns
     *   New rotation matrix
     */
    static Matrix4 Rotate(const Quaternion& q) noexcept;
    
    /**
     * @method Perspective
     * @brief Create perspective projection matrix
     * 
     * @params
     *   - fovy (float): Vertical field of view in radians
     *   - aspect (float): Aspect ratio (width/height)
     *   - znear (float): Near clipping plane
     *   - zfar (float): Far clipping plane
     * 
     * @returns
     *   New perspective projection matrix
     */
    static Matrix4 Perspective(float fovy, float aspect, float znear, float zfar) noexcept;
    
    /**
     * @method Orthographic
     * @brief Create orthographic projection matrix
     * 
     * @params
     *   - left, right, bottom, top, znear, zfar (float): Frustum bounds
     * 
     * @returns
     *   New orthographic projection matrix
     */
    static Matrix4 Orthographic(float left, float right, float bottom, float top, 
                                float znear, float zfar) noexcept;
    
    /**
     * @method LookAt
     * @brief Create view matrix
     * 
     * @params
     *   - eye (const Vector3&): Camera position
     *   - center (const Vector3&): Look-at point
     *   - up (const Vector3&): Up direction
     * 
     * @returns
     *   New view matrix
     */
    static Matrix4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) noexcept;
    
    /**
     * @method Transpose
     * @brief Get transposed matrix
     * 
     * @params (none)
     * 
     * @returns
     *   New transposed matrix
     */
    Matrix4 Transpose() const noexcept {
        return Matrix4(glm::transpose(data));
    }
    
    /**
     * @method Inverse
     * @brief Get inverted matrix
     * 
     * @params (none)
     * 
     * @returns
     *   New inverted matrix
     * 
     * @notes
     *   - Slower operation (O(n³))
     *   - Singular matrices return undefined results
     */
    Matrix4 Inverse() const noexcept {
        return Matrix4(glm::inverse(data));
    }
    
    /**
     * @method Determinant
     * @brief Get matrix determinant
     * 
     * @params (none)
     * 
     * @returns
     *   (float) Determinant value
     */
    float Determinant() const noexcept {
        return glm::determinant(data);
    }
    
    bool operator==(const Matrix4& other) const noexcept;
    bool operator!=(const Matrix4& other) const noexcept;
    
    // Element access
    glm::vec4 operator[](int row) const noexcept {
        return data[row];
    }
    
    glm::vec4& operator[](int row) noexcept {
        return data[row];
    }
    
    /**
     * @method Identity
     * @brief Get identity matrix
     * 
     * @params (none)
     * 
     * @returns
     *   Identity matrix (1 on diagonal, 0 elsewhere)
     */
    static Matrix4 Identity() noexcept {
        return Matrix4(glm::mat4(1.0f));
    }
    
    std::string ToString() const;
};

} // namespace threecpp
