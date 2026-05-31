add_executable(hello_triangle hello_triangle.cpp)
target_link_libraries(hello_triangle PRIVATE ThreeCPP)

add_executable(cube_rotation cube_rotation.cpp)
target_link_libraries(cube_rotation PRIVATE ThreeCPP)
