enable_testing()

# Math tests
add_executable(test_math math_test.cpp)
target_link_libraries(test_math PRIVATE ThreeCPP)
add_test(NAME MathTests COMMAND test_math)

# Scene tests
add_executable(test_scene scene_test.cpp)
target_link_libraries(test_scene PRIVATE ThreeCPP)
add_test(NAME SceneTests COMMAND test_scene)
