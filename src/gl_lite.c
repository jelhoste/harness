#include "gl_lite.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM2FVPROC glUniform2fv = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;

PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;

PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;

PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;

PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = NULL;
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = NULL;

// Charge un symbole et râle proprement (avec son nom) s'il est introuvable,
// plutôt que de planter plus loin avec un crash difficile à diagnostiquer.
#define NOVA_LOAD(name) \
    do { \
        *(void**)(&(name)) = (void*)glfwGetProcAddress(#name); \
        if (!(name)) { \
            fprintf(stderr, "[gl_lite] symbole OpenGL introuvable : %s\n", #name); \
            ok = 0; \
        } \
    } while (0)

int nova_gl_lite_init(void)
{
    int ok = 1;

    NOVA_LOAD(glCreateShader);
    NOVA_LOAD(glShaderSource);
    NOVA_LOAD(glCompileShader);
    NOVA_LOAD(glGetShaderiv);
    NOVA_LOAD(glGetShaderInfoLog);
    NOVA_LOAD(glDeleteShader);
    NOVA_LOAD(glCreateProgram);
    NOVA_LOAD(glAttachShader);
    NOVA_LOAD(glBindAttribLocation);
    NOVA_LOAD(glLinkProgram);
    NOVA_LOAD(glGetProgramiv);
    NOVA_LOAD(glGetProgramInfoLog);
    NOVA_LOAD(glDeleteProgram);
    NOVA_LOAD(glUseProgram);
    NOVA_LOAD(glGetUniformLocation);
    NOVA_LOAD(glUniform1i);
    NOVA_LOAD(glUniform2fv);
    NOVA_LOAD(glUniform4fv);

    NOVA_LOAD(glGenBuffers);
    NOVA_LOAD(glBindBuffer);
    NOVA_LOAD(glBufferData);
    NOVA_LOAD(glBufferSubData);
    NOVA_LOAD(glDeleteBuffers);

    NOVA_LOAD(glGenVertexArrays);
    NOVA_LOAD(glBindVertexArray);
    NOVA_LOAD(glDeleteVertexArrays);

    NOVA_LOAD(glVertexAttribPointer);
    NOVA_LOAD(glEnableVertexAttribArray);
    NOVA_LOAD(glDisableVertexAttribArray);

    NOVA_LOAD(glActiveTexture);
    NOVA_LOAD(glBlendFuncSeparate);
    NOVA_LOAD(glStencilOpSeparate);

    return ok;
}
