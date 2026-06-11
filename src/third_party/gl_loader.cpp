#include "../../include/threecpp/gl_loader.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

namespace threecpp::gl {

PFNGLGENVERTEXARRAYSPROC GenVertexArrays = nullptr;
PFNGLGENBUFFERSPROC GenBuffers = nullptr;
PFNGLBINDVERTEXARRAYPROC BindVertexArray = nullptr;
PFNGLBINDBUFFERPROC BindBuffer = nullptr;
PFNGLBUFFERDATAPROC BufferData = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC VertexAttribPointer = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC EnableVertexAttribArray = nullptr;
PFNGLCREATESHADERPROC CreateShader = nullptr;
PFNGLSHADERSOURCEPROC ShaderSource = nullptr;
PFNGLCOMPILESHADERPROC CompileShader = nullptr;
PFNGLCREATEPROGRAMPROC CreateProgram = nullptr;
PFNGLATTACHSHADERPROC AttachShader = nullptr;
PFNGLLINKPROGRAMPROC LinkProgram = nullptr;
PFNGLGETPROGRAMIVPROC GetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC GetProgramInfoLog = nullptr;
PFNGLGETSHADERIVPROC GetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC GetShaderInfoLog = nullptr;
PFNGLDELETESHADERPROC DeleteShader = nullptr;
PFNGLDELETEPROGRAMPROC DeleteProgram = nullptr;
PFNGLUSEPROGRAMPROC UseProgram = nullptr;
PFNGLGETUNIFORMLOCATIONPROC GetUniformLocation = nullptr;
PFNGLUNIFORMMATRIX4FVPROC UniformMatrix4fv = nullptr;
PFNGLDRAWARRAYSPROC DrawArrays = nullptr;
PFNGLDELETEBUFFERSPROC DeleteBuffers = nullptr;
PFNGLDELETEVERTEXARRAYSPROC DeleteVertexArrays = nullptr;
PFNGLVIEWPORTPROC Viewport = nullptr;
PFNGLCLEARCOLORPROC ClearColor = nullptr;
PFNGLCLEARPROC Clear = nullptr;

int Init() {
    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GenVertexArrays = glGenVertexArrays;
    GenBuffers = glGenBuffers;
    BindVertexArray = glBindVertexArray;
    BindBuffer = glBindBuffer;
    BufferData = glBufferData;
    VertexAttribPointer = glVertexAttribPointer;
    EnableVertexAttribArray = glEnableVertexAttribArray;
    CreateShader = glCreateShader;
    ShaderSource = glShaderSource;
    CompileShader = glCompileShader;
    CreateProgram = glCreateProgram;
    AttachShader = glAttachShader;
    LinkProgram = glLinkProgram;
    GetProgramiv = glGetProgramiv;
    GetProgramInfoLog = glGetProgramInfoLog;
    GetShaderiv = glGetShaderiv;
    GetShaderInfoLog = glGetShaderInfoLog;
    DeleteShader = glDeleteShader;
    DeleteProgram = glDeleteProgram;
    UseProgram = glUseProgram;
    GetUniformLocation = glGetUniformLocation;
    UniformMatrix4fv = glUniformMatrix4fv;
    DrawArrays = glDrawArrays;
    DeleteBuffers = glDeleteBuffers;
    DeleteVertexArrays = glDeleteVertexArrays;
    Viewport = glViewport;
    ClearColor = glClearColor;
    Clear = glClear;

    if (!CreateShader || !CreateProgram || !GenVertexArrays) {
        std::cerr << "Critical GL functions not loaded; check loader." << std::endl;
        return -1;
    }
    return 0;
}

} // namespace threecpp::gl
