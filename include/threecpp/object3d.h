#pragma once
/**
 * @class Object3D
 * @brief Base class for all 3D objects in the scene
 * 
 * @details
 * Base class for Scene, Mesh, Light, Camera, etc.
 * Handles:
 * - Position, rotation, scale (transformation)
 * - Parent-child hierarchy
 * - Visibility
 * - Matrix caching
 * 
 * Mirrors three.js Object3D exactly for API parity.
 * 
 * @performance
 *   - Transform updates: O(1) per object
 *   - World matrix propagation: O(n) where n = depth in hierarchy
 * 
 * @thread_safe
 *   - Each object should be accessed from single thread
 *   - Multiple objects can be modified simultaneously
 */

#include "vector3.h"
#include "quaternion.h"
#include "matrix4.h"
#include "euler.h"

#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <cstdint>

namespace threecpp {

class Object3D : public std::enable_shared_from_this<Object3D> {
public:
    using Ptr = std::shared_ptr<Object3D>;
    using WeakPtr = std::weak_ptr<Object3D>;
    using ChildList = std::vector<Ptr>;
    
    // ===== Transform Properties =====
    
    /**
     * @property position
     * @brief Local position relative to parent
     * 
     * @example
     * ```cpp
     * obj->position = Vector3(1, 2, 3);
     * obj->position.x = 5;
     * ```
     */
    Vector3 position{0, 0, 0};
    
    /**
     * @property rotation
     * @brief Euler angles (automatically synced with quaternion)
     * 
     * @notes
     *   Modifying this updates the quaternion
     */
    Euler rotation;
    
    /**
     * @property quaternion
     * @brief Rotation as quaternion (automatically synced with Euler angles)
     * 
     * @notes
     *   Modifying this updates Euler angles
     */
    Quaternion quaternion{0, 0, 0, 1};
    
    /**
     * @property scale
     * @brief Local scale factors
     * 
     * @notes
     *   (1, 1, 1) = no scaling
     *   (2, 2, 2) = 2x larger
     *   (0.5, 1, 1) = half width, normal height/depth
     */
    Vector3 scale{1, 1, 1};
    
    // ===== Hierarchy Properties =====
    
    /**
     * @property parent
     * @brief Parent object in hierarchy
     * 
     * @notes
     *   nullptr for root objects
     */
    WeakPtr parent;
    
    /**
     * @property children
     * @brief Array of child objects
     */
    ChildList children;
    
    // ===== Visibility & Metadata =====
    
    /**
     * @property visible
     * @brief Whether this object is rendered
     * 
     * @notes
     *   - Hidden objects don't render and don't update children
     *   - Affects entire subtree
     */
    bool visible = true;
    
    /**
     * @property matrixAutoUpdate
     * @brief Automatically update matrix when transform changes
     * 
     * @notes
     *   If false, must manually call UpdateMatrix()
     */
    bool matrix_auto_update = true;
    
    /**
     * @property name
     * @brief Object name for identification and debugging
     */
    std::string name;
    
    /**
     * @property uuid
     * @brief Unique identifier (auto-generated)
     */
    std::string uuid;
    
    /**
     * @property userData
     * @brief User-defined data (arbitrary key-value storage)
     */
    std::map<std::string, std::string> user_data;
    
    // ===== Constructor / Destructor =====
    
    Object3D();
    virtual ~Object3D() = default;
    
    // Delete copy semantics (use shared_ptr instead)
    Object3D(const Object3D&) = delete;
    Object3D& operator=(const Object3D&) = delete;
    
    // Allow move semantics
    Object3D(Object3D&&) noexcept = default;
    Object3D& operator=(Object3D&&) noexcept = default;
    
    // ===== Hierarchy Management =====
    
    /**
     * @method Add
     * @brief Add child object(s)
     * 
     * @params
     *   - child (const Ptr&): Child object to add
     *   - ... (Ptr): Additional children
     * 
     * @returns
     *   (Ptr) Returns this for chaining
     * 
     * @example
     * ```cpp
     * auto parent = std::make_shared<Object3D>();
     * auto child1 = std::make_shared<Mesh>(...);
     * auto child2 = std::make_shared<Mesh>(...);
     * parent->Add(child1);
     * parent->Add(child2);
     * ```
     */
    Ptr Add(const Ptr& child) {
        if (child == shared_from_this()) {
            throw std::runtime_error("Object cannot be added to itself");
        }
        if (auto old_parent = child->parent.lock()) {
            old_parent->Remove(child);
        }
        child->parent = shared_from_this();
        children.push_back(child);
        return shared_from_this();
    }
    
    /**
     * @method Remove
     * @brief Remove child object(s)
     * 
     * @params
     *   - child (const Ptr&): Child to remove
     * 
     * @returns
     *   (Ptr) Returns this for chaining
     */
    Ptr Remove(const Ptr& child) {
        auto it = std::find(children.begin(), children.end(), child);
        if (it != children.end()) {
            child->parent.reset();
            children.erase(it);
        }
        return shared_from_this();
    }
    
    /**
     * @method GetParent
     * @brief Get parent object (safe, returns nullptr if no parent)
     * 
     * @params (none)
     * 
     * @returns
     *   Parent Ptr or nullptr
     */
    Ptr GetParent() const {
        return parent.lock();
    }
    
    // ===== Transformation =====
    
    /**
     * @method UpdateMatrix
     * @brief Recalculate local transformation matrix from position/rotation/scale
     * 
     * @params (none)
     * 
     * @returns (void)
     * 
     * @notes
     *   Called automatically if matrixAutoUpdate is true
     */
    void UpdateMatrix();
    
    /**
     * @method UpdateMatrixWorld
     * @brief Recursively update world transformation matrices
     * 
     * @params
     *   - force (bool): Force update even if unchanged. Default: false
     * 
     * @returns (void)
     * 
     * @notes
     *   Called every frame by renderer
     *   Propagates parent transforms down the hierarchy
     */
    void UpdateMatrixWorld(bool force = false);
    
    /**
     * @method GetWorldPosition
     * @brief Get position in world space
     * 
     * @params (none)
     * 
     * @returns
     *   Vector3 in world coordinates
     */
    Vector3 GetWorldPosition() const;
    
    /**
     * @method GetWorldQuaternion
     * @brief Get rotation in world space
     * 
     * @params (none)
     * 
     * @returns
     *   Quaternion in world space
     */
    Quaternion GetWorldQuaternion() const;
    
    /**
     * @method GetWorldScale
     * @brief Get scale in world space
     * 
     * @params (none)
     * 
     * @returns
     *   Vector3 scale in world space
     */
    Vector3 GetWorldScale() const;
    
    /**
     * @method GetWorldMatrix
     * @brief Get complete world transformation matrix
     * 
     * @params (none)
     * 
     * @returns
     *   Reference to world matrix (read-only)
     */
    const Matrix4& GetWorldMatrix() const {
        return m_world_matrix;
    }
    
    /**
     * @method GetLocalMatrix
     * @brief Get local transformation matrix
     * 
     * @params (none)
     * 
     * @returns
     *   Reference to local matrix
     */
    const Matrix4& GetLocalMatrix() const {
        return m_local_matrix;
    }
    
    /**
     * @method LookAt
     * @brief Rotate to look at a point
     * 
     * @params
     *   - target (const Vector3&): Point to look at in world space
     *   - up (const Vector3&): Up direction. Default: +Y
     * 
     * @returns (void)
     * 
     * @notes
     *   Camera and Mesh typically look down -Z axis
     */
    void LookAt(const Vector3& target, const Vector3& up = Vector3::Up());
    
    // ===== Scene Graph Traversal =====
    
    /**
     * @method Traverse
     * @brief Execute function on this object and all descendants
     * 
     * @params
     *   - callback (function): Called with each Object3D*
     * 
     * @returns (void)
     * 
     * @example
     * ```cpp
     * scene->Traverse([](Object3D* obj) {
     *     std::cout << obj->name << std::endl;
     * });
     * ```
     */
    void Traverse(std::function<void(Object3D*)> callback);
    
    /**
     * @method TraverseVisible
     * @brief Traverse only visible objects
     * 
     * @params
     *   - callback (function): Called with visible Object3D*
     * 
     * @returns (void)
     */
    void TraverseVisible(std::function<void(Object3D*)> callback);
    
    /**
     * @method GetObjectByName
     * @brief Find child by name (deep search)
     * 
     * @params
     *   - name (const std::string&): Name to find
     * 
     * @returns
     *   First matching object or nullptr
     */
    Ptr GetObjectByName(const std::string& name);
    
    /**
     * @method GetObjectById
     * @brief Find child by ID (deep search)
     * 
     * @params
     *   - id (uint32_t): ID to find
     * 
     * @returns
     *   Matching object or nullptr
     */
    Ptr GetObjectById(uint32_t id);
    
    // ===== Utility =====
    
    /**
     * @method GetFront
     * @brief Get forward direction (typically -Z)
     * 
     * @params (none)
     * 
     * @returns
     *   Normalized forward vector in world space
     */
    Vector3 GetFront() const;
    
    /**
     * @method GetRight
     * @brief Get right direction
     * 
     * @params (none)
     * 
     * @returns
     *   Normalized right vector in world space
     */
    Vector3 GetRight() const;
    
    /**
     * @method GetUp
     * @brief Get up direction
     * 
     * @params (none)
     * 
     * @returns
     *   Normalized up vector in world space
     */
    Vector3 GetUp() const;
    
    /**
     * @method Clone
     * @brief Create deep copy of this object and children
     * 
     * @params
     *   - recursive (bool): Also clone children. Default: true
     * 
     * @returns
     *   New Object3D with copied properties
     */
    virtual Ptr Clone(bool recursive = true);
    
    /**
     * @method ToString
     * @brief Get string representation for debugging
     * 
     * @params (none)
     * 
     * @returns
     *   String describing object
     */
    virtual std::string ToString() const;
    
    // Type identification (for RTTI without RTTI)
    virtual const char* GetTypeName() const {
        return "Object3D";
    }
    
protected:
    Matrix4 m_local_matrix{Matrix4::Identity()};
    Matrix4 m_world_matrix{Matrix4::Identity()};
    
    // Track if world matrix needs update
    bool m_world_matrix_needs_update = true;
    
    /**
     * @method OnMatrixChanged
     * @brief Called when local matrix is modified
     * 
     * @notes
     *   Override to react to transform changes
     */
    virtual void OnMatrixChanged() {}
};

} // namespace threecpp
