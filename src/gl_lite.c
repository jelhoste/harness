#include "gl_lite.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

PFNGLCREATESHADERPROC nova_glCreateShader = NULL;
PFNGLSHADERSOURCEPROC nova_glShaderSource = NULL;
PFNGLCOMPILESHADERPROC nova_glCompileShader = NULL;
PFNGLGETSHADERIVPROC nova_glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC nova_glGetShaderInfoLog = NULL;
PFNGLDELETESHADERPROC nova_glDeleteShader = NULL;
PFNGLCREATEPROGRAMPROC nova_glCreateProgram = NULL;
PFNGLATTACHSHADERPROC nova_glAttachShader = NULL;
PFNGLBINDATTRIBLOCATIONPROC nova_glBindAttribLocation = NULL;
PFNGLLINKPROGRAMPROC nova_glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC nova_glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC nova_glGetProgramInfoLog = NULL;
PFNGLDELETEPROGRAMPROC nova_glDeleteProgram = NULL;
PFNGLUSEPROGRAMPROC nova_glUseProgram = NULL;
PFNGLGETUNIFORMLOCATIONPROC nova_glGetUniformLocation = NULL;
PFNGLUNIFORM1IPROC nova_glUniform1i = NULL;
PFNGLUNIFORM2FVPROC nova_glUniform2fv = NULL;
PFNGLUNIFORM4FVPROC nova_glUniform4fv = NULL;

PFNGLGENBUFFERSPROC nova_glGenBuffers = NULL;
PFNGLBINDBUFFERPROC nova_glBindBuffer = NULL;
PFNGLBUFFERDATAPROC nova_glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC nova_glBufferSubData = NULL;
PFNGLDELETEBUFFERSPROC nova_glDeleteBuffers = NULL;

PFNGLGENVERTEXARRAYSPROC nova_glGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC nova_glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC nova_glDeleteVertexArrays = NULL;

PFNGLVERTEXATTRIBPOINTERPROC nova_glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC nova_glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC nova_glDisableVertexAttribArray = NULL;

PFNGLACTIVETEXTUREPROC nova_glActiveTexture = NULL;
PFNGLBLENDFUNCSEPARATEPROC nova_glBlendFuncSeparate = NULL;
PFNGLSTENCILOPSEPARATEPROC nova_glStencilOpSeparate = NULL;
PFNGLGENERATEMIPMAPPROC nova_glGenerateMipmap = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC nova_glGetUniformBlockIndex = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC nova_glUniformBlockBinding = NULL;
PFNGLBINDBUFFERBASEPROC nova_glBindBufferBase = NULL;
PFNGLBINDBUFFERRANGEPROC nova_glBindBufferRange = NULL;

// Charge un symbole (identifié par son vrai nom OpenGL, passé en chaîne
// littérale pour ne pas passer par la macro de redirection) et râle
// proprement s'il est introuvable.
#define NOVA_LOAD(realname_str, var) \
    do { \
        *(void**)(&(var)) = (void*)glfwGetProcAddress(realname_str); \
        if (!(var)) { \
            fprintf(stderr, "[gl_lite] symbole OpenGL introuvable : %s\n", realname_str); \
            ok = 0; \
        } \
    } while (0)

int nova_gl_lite_init(void)
{
    int ok = 1;

    NOVA_LOAD("glCreateShader", nova_glCreateShader);
    NOVA_LOAD("glShaderSource", nova_glShaderSource);
    NOVA_LOAD("glCompileShader", nova_glCompileShader);
    NOVA_LOAD("glGetShaderiv", nova_glGetShaderiv);
    NOVA_LOAD("glGetShaderInfoLog", nova_glGetShaderInfoLog);
    NOVA_LOAD("glDeleteShader", nova_glDeleteShader);
    NOVA_LOAD("glCreateProgram", nova_glCreateProgram);
    NOVA_LOAD("glAttachShader", nova_glAttachShader);
    NOVA_LOAD("glBindAttribLocation", nova_glBindAttribLocation);
    NOVA_LOAD("glLinkProgram", nova_glLinkProgram);
    NOVA_LOAD("glGetProgramiv", nova_glGetProgramiv);
    NOVA_LOAD("glGetProgramInfoLog", nova_glGetProgramInfoLog);
    NOVA_LOAD("glDeleteProgram", nova_glDeleteProgram);
    NOVA_LOAD("glUseProgram", nova_glUseProgram);
    NOVA_LOAD("glGetUniformLocation", nova_glGetUniformLocation);
    NOVA_LOAD("glUniform1i", nova_glUniform1i);
    NOVA_LOAD("glUniform2fv", nova_glUniform2fv);
    NOVA_LOAD("glUniform4fv", nova_glUniform4fv);

    NOVA_LOAD("glGenBuffers", nova_glGenBuffers);
    NOVA_LOAD("glBindBuffer", nova_glBindBuffer);
    NOVA_LOAD("glBufferData", nova_glBufferData);
    NOVA_LOAD("glBufferSubData", nova_glBufferSubData);
    NOVA_LOAD("glDeleteBuffers", nova_glDeleteBuffers);

    NOVA_LOAD("glGenVertexArrays", nova_glGenVertexArrays);
    NOVA_LOAD("glBindVertexArray", nova_glBindVertexArray);
    NOVA_LOAD("glDeleteVertexArrays", nova_glDeleteVertexArrays);

    NOVA_LOAD("glVertexAttribPointer", nova_glVertexAttribPointer);
    NOVA_LOAD("glEnableVertexAttribArray", nova_glEnableVertexAttribArray);
    NOVA_LOAD("glDisableVertexAttribArray", nova_glDisableVertexAttribArray);

    NOVA_LOAD("glActiveTexture", nova_glActiveTexture);
    NOVA_LOAD("glBlendFuncSeparate", nova_glBlendFuncSeparate);
    NOVA_LOAD("glStencilOpSeparate", nova_glStencilOpSeparate);
    NOVA_LOAD("glGenerateMipmap", nova_glGenerateMipmap);
    NOVA_LOAD("glGetUniformBlockIndex", nova_glGetUniformBlockIndex);
    NOVA_LOAD("glUniformBlockBinding", nova_glUniformBlockBinding);
    NOVA_LOAD("glBindBufferBase", nova_glBindBufferBase);
    NOVA_LOAD("glBindBufferRange", nova_glBindBufferRange);

    return ok;
}
