/**
 * Scene Graph Tests
 */

#include <threecpp/threecpp.h>
#include <iostream>
#include <cassert>

using namespace threecpp;

void test_scene_hierarchy() {
    auto scene = std::make_shared<Scene>();
    auto obj1 = std::make_shared<Object3D>();
    auto obj2 = std::make_shared<Object3D>();
    auto obj3 = std::make_shared<Object3D>();
    
    obj1->name = "Object1";
    obj2->name = "Object2";
    obj3->name = "Object3";
    
    // Build hierarchy
    scene->Add(obj1);
    obj1->Add(obj2);
    obj1->Add(obj3);
    
    // Test hierarchy
    assert(obj1->children.size() == 2);
    assert(obj2->GetParent() == obj1);
    assert(obj3->GetParent() == obj1);
    
    std::cout << "✓ Scene hierarchy tests passed" << std::endl;
}

void test_transforms() {
    auto obj = std::make_shared<Object3D>();
    
    // Set local transform
    obj->position = Vector3(1, 2, 3);
    obj->scale = Vector3(2, 2, 2);
    obj->rotation.y = 3.14159f / 2.0f;
    
    // Update matrices
    obj->UpdateMatrix();
    obj->UpdateMatrixWorld();
    
    // Check world position (no parent, so should match local)
    Vector3 world_pos = obj->GetWorldPosition();
    assert(std::abs(world_pos.x - 1.0f) < 0.01f);
    assert(std::abs(world_pos.y - 2.0f) < 0.01f);
    assert(std::abs(world_pos.z - 3.0f) < 0.01f);
    
    std::cout << "✓ Transform tests passed" << std::endl;
}

void test_object_search() {
    auto scene = std::make_shared<Scene>();
    auto mesh1 = std::make_shared<Mesh>();
    auto mesh2 = std::make_shared<Mesh>();
    
    mesh1->name = "Mesh1";
    mesh2->name = "Mesh2";
    
    scene->Add(mesh1);
    mesh1->Add(mesh2);
    
    // Find by name
    auto found = scene->GetObjectByName("Mesh2");
    assert(found != nullptr);
    assert(found->name == "Mesh2");
    
    std::cout << "✓ Object search tests passed" << std::endl;
}

int main() {
    std::cout << "Running scene graph tests..." << std::endl;
    
    test_scene_hierarchy();
    test_transforms();
    test_object_search();
    
    std::cout << "\n✓ All scene tests passed!" << std::endl;
    return 0;
}
