# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(SoftwareRenderer)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add GLFW as a subdirectory to build it from source
add_subdirectory(libs/glfw)

set(SOURCES
    src/main.cpp
    src/Logger.cpp
    src/Cube.cpp
    src/Tetrahedron.cpp
    src/Octahedron.cpp
    src/Sphere.cpp
    src/Cone.cpp
    src/Cylinder.cpp
    src/Renderer.cpp
    src/GUI.cpp
)

# Create the main executable
add_executable(renderer ${SOURCES})

# Set OpenGL preference to GLVND (use LEGACY if preferred instead)
set(OpenGL_GL_PREFERENCE GLVND)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Set up ImGui as a static library using source files from libs/imgui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/libs/imgui)
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Set include directories for ImGui (public so linking targets inherit them)
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Link ImGui against GLFW and OpenGL (private since ImGui is static)
target_link_libraries(imgui PRIVATE glfw OpenGL::GL)

# Link the main executable against ImGui, GLFW, and OpenGL
target_link_libraries(renderer PRIVATE imgui glfw OpenGL::GL)

# Set include directories for the renderer target
target_include_directories(renderer PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/libs/glm
)

# Optionally, set GLFW build options to disable unnecessary builds
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
