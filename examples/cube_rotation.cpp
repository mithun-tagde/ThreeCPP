/**
 * Cube Rotation Example
 * 
 * Renders a rotating colored cube with lighting.
 * Demonstrates geometry, materials, and lighting.
 */

#include <threecpp/threecpp.h>
#include <iostream>

using namespace threecpp;

int main() {
    // Create renderer
    RendererConfig config;
    config.width = 1024;
    config.height = 768;
    config.title = "ThreeCPP - Rotating Cube";
    
    auto renderer = CreateRenderer(config);
    
    // Create scene
    auto scene = std::make_shared<Scene>();
    
    // Create camera
    auto camera = std::make_shared<PerspectiveCamera>(
        75.0f, 1024.0f / 768.0f, 0.1f, 1000.0f
    );
    camera->position = Vector3(0, 2, 5);
    camera->LookAt(Vector3(0, 0, 0));
    
    // Create cube geometry
    auto geometry = std::make_shared<BoxGeometry>(1.0f, 1.0f, 1.0f);
    
    // Create material
    auto material = std::make_shared<MeshPhongMaterial>();
    material->color = Color(0xFF2040);  // Magenta
    material->emissive = Color::Black();
    material->specular = Color(0x111111);
    material->shininess = 50.0f;
    
    // Create mesh
    auto cube = std::make_shared<Mesh>(geometry, material);
    scene->Add(cube);
    
    // Add ambient light
    auto ambient = std::make_shared<AmbientLight>(Color::White(), 0.5f);
    scene->Add(ambient);
    
    // Add directional light
    auto sun = std::make_shared<DirectionalLight>(Color::White(), 1.0f);
    sun->position = Vector3(5, 8, 5);
    scene->Add(sun);
    
    std::cout << "Rendering rotating cube..." << std::endl;
    
    // Render loop
    float time = 0.0f;
    while (renderer->IsRunning()) {
        time += 0.016f;  // Assume 60 FPS
        
        // Rotate cube
        cube->rotation.x = time * 0.5f;
        cube->rotation.y = time * 0.7f;
        
        // Render
        renderer->Render(scene, camera);
    }
    
    return 0;
}
