/**
 * Hello Triangle Example
 * 
 * Minimal example rendering a simple colored triangle.
 * Demonstrates basic ThreeCPP usage.
 */

#include <threecpp/threecpp.h>
#include <iostream>

using namespace threecpp;

int main() {
    std::cout << "ThreeCPP v" << GetVersion() << std::endl;
    
    // Create renderer with configuration
    RendererConfig config;
    config.width = 800;
    config.height = 600;
    config.title = "ThreeCPP - Hello Triangle";
    
    auto renderer = CreateRenderer(config);
    
    // Create scene
    auto scene = std::make_shared<Scene>();
    
    // Create perspective camera
    auto camera = std::make_shared<PerspectiveCamera>(
        75.0f,  // FOV in degrees
        800.0f / 600.0f,  // Aspect ratio
        0.1f,   // Near plane
        1000.0f // Far plane
    );
    camera->position = Vector3(0, 0, 3);
    
    // Create simple triangle geometry
    auto geometry = std::make_shared<Geometry>();
    geometry->vertices = {
        Vector3(-1, -1, 0),
        Vector3(1, -1, 0),
        Vector3(0, 1, 0)
    };
    geometry->faces = { 0, 1, 2 };
    
    // Create material
    auto material = std::make_shared<MeshBasicMaterial>();
    material->color = Color(0.2f, 0.5f, 0.8f);  // Blue
    
    // Create mesh and add to scene
    auto mesh = std::make_shared<Mesh>(geometry, material);
    scene->Add(mesh);
    
    std::cout << "Rendering triangle (close window to exit)..." << std::endl;
    
    // Render loop
    while (renderer->IsRunning()) {
        // Update
        mesh->rotation.z += 0.01f;
        
        // Render
        renderer->Render(scene, camera);
    }
    
    std::cout << "Goodbye!" << std::endl;
    return 0;
}
