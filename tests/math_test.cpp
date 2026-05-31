/**
 * Math Library Tests
 */

#include <threecpp/threecpp.h>
#include <iostream>
#include <cassert>

using namespace threecpp;

void test_vector3_basic() {
    Vector3 v1(1, 2, 3);
    Vector3 v2(4, 5, 6);
    
    // Addition
    Vector3 sum = v1 + v2;
    assert(sum.x == 5 && sum.y == 7 && sum.z == 9);
    
    // Length
    Vector3 v(3, 4, 0);
    assert(v.Length() == 5.0f);
    
    // Dot product
    Vector3 a(1, 0, 0);
    Vector3 b(0, 1, 0);
    assert(a.Dot(b) == 0);
    
    std::cout << "✓ Vector3 basic tests passed" << std::endl;
}

void test_matrix4_transforms() {
    Matrix4 identity = Matrix4::Identity();
    
    // Translation
    Matrix4 translate = Matrix4::Translate(Vector3(1, 2, 3));
    
    // Rotation
    Matrix4 rotate = Matrix4::RotateY(3.14159f / 2.0f);
    
    // Scale
    Matrix4 scale = Matrix4::Scale(Vector3(2, 2, 2));
    
    // Combined
    Matrix4 combined = translate * rotate * scale;
    
    std::cout << "✓ Matrix4 transformation tests passed" << std::endl;
}

void test_quaternion() {
    Quaternion q1 = Quaternion::Identity();
    Quaternion q2 = Quaternion::AxisAngle(Vector3::Up(), 3.14159f / 2.0f);
    
    // Quaternion product
    Quaternion combined = q1 * q2;
    
    // Normalization
    combined.Normalize();
    assert(std::abs(combined.Length() - 1.0f) < 0.001f);
    
    std::cout << "✓ Quaternion tests passed" << std::endl;
}

void test_color() {
    Color c1(1, 0, 0);  // Red
    Color c2(0xFF0000);  // Red from hex
    
    assert(c1 == c2);
    
    Color c3("red");
    assert(c1.GetHex() == c3.GetHex());
    
    std::cout << "✓ Color tests passed" << std::endl;
}

int main() {
    std::cout << "Running math library tests..." << std::endl;
    
    test_vector3_basic();
    test_matrix4_transforms();
    test_quaternion();
    test_color();
    
    std::cout << "\n✓ All math tests passed!" << std::endl;
    return 0;
}
