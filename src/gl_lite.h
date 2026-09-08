// Nova — loader OpenGL minimal
//
// Sous Windows, opengl32.dll n'exporte directement que les fonctions
// OpenGL 1.1. Tout ce qui est plus récent (shaders, buffers, VAO...)
// doit être récupéré à l'exécution via un pointeur de fonction, obtenu
// avec glfwGetProcAddress(). C'est le rôle de ce fichier.
//
// On ne charge ici QUE les fonctions dont NanoVG (backend GL3) a besoin,
// plutôt qu'un loader générique complet — plus simple à maintenir, pas
// de dépendance externe (Python/glad).
//
// Chaque fonction est stockée dans une variable nova_glXxx, puis un
// #define redirige le nom standard (glXxx) vers cette variable. Ça évite
// tout conflit avec les fonctions que l'en-tête système déclarerait déjà
// de son côté (le cas varie selon l'OS : Windows n'en déclare presque
// aucune, Linux/Mesa une partie, macOS quasiment toutes en version
// dépréciée) — on ne dépend plus de ce que le système fournit.

#ifndef NOVA_GL_LITE_H
#define NOVA_GL_LITE_H

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #ifdef _WIN32
        #include <windows.h>
    #endif
    #include <GL/gl.h>
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// --- Types manquants dans les en-têtes GL 1.1 -----------------------------
#ifndef GL_VERSION_2_0
typedef char GLchar;
#endif
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;

// --- Enums utilisés par NanoVG (backend GL3), absents de certains en-têtes
#ifndef GL_ARRAY_BUFFER
#define GL_ARRAY_BUFFER                    0x8892
#endif
#ifndef GL_ELEMENT_ARRAY_BUFFER
#define GL_ELEMENT_ARRAY_BUFFER            0x8893
#endif
#ifndef GL_STREAM_DRAW
#define GL_STREAM_DRAW                     0x88E0
#endif
#ifndef GL_STATIC_DRAW
#define GL_STATIC_DRAW                     0x88E4
#endif
#ifndef GL_DYNAMIC_DRAW
#define GL_DYNAMIC_DRAW                    0x88E8
#endif
#ifndef GL_FRAGMENT_SHADER
#define GL_FRAGMENT_SHADER                 0x8B30
#endif
#ifndef GL_VERTEX_SHADER
#define GL_VERTEX_SHADER                   0x8B31
#endif
#ifndef GL_COMPILE_STATUS
#define GL_COMPILE_STATUS                  0x8B81
#endif
#ifndef GL_LINK_STATUS
#define GL_LINK_STATUS                     0x8B82
#endif
#ifndef GL_INFO_LOG_LENGTH
#define GL_INFO_LOG_LENGTH                 0x8B84
#endif
#ifndef GL_TEXTURE0
#define GL_TEXTURE0                        0x84C0
#endif
#ifndef GL_RED
#define GL_RED                             0x1903
#endif
#ifndef GL_TEXTURE_SWIZZLE_RGBA
#define GL_TEXTURE_SWIZZLE_RGBA            0x8E46
#endif
#ifndef GL_FRAMEBUFFER_SRGB
#define GL_FRAMEBUFFER_SRGB                0x8DB9
#endif
#ifndef GL_UNIFORM_BUFFER
#define GL_UNIFORM_BUFFER                  0x8A11
#endif
#ifndef GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE                   0x812F
#endif
#ifndef GL_INCR_WRAP
#define GL_INCR_WRAP                       0x8507
#endif
#ifndef GL_DECR_WRAP
#define GL_DECR_WRAP                       0x8508
#endif

// --- Déclaration + redirection macro, une fonction à la fois -------------
typedef GLuint (*PFNGLCREATESHADERPROC)(GLenum type);
extern PFNGLCREATESHADERPROC nova_glCreateShader;
#define glCreateShader nova_glCreateShader

typedef void (*PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
extern PFNGLSHADERSOURCEPROC nova_glShaderSource;
#define glShaderSource nova_glShaderSource

typedef void (*PFNGLCOMPILESHADERPROC)(GLuint shader);
extern PFNGLCOMPILESHADERPROC nova_glCompileShader;
#define glCompileShader nova_glCompileShader

typedef void (*PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint* params);
extern PFNGLGETSHADERIVPROC nova_glGetShaderiv;
#define glGetShaderiv nova_glGetShaderiv

typedef void (*PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
extern PFNGLGETSHADERINFOLOGPROC nova_glGetShaderInfoLog;
#define glGetShaderInfoLog nova_glGetShaderInfoLog

typedef void (*PFNGLDELETESHADERPROC)(GLuint shader);
extern PFNGLDELETESHADERPROC nova_glDeleteShader;
#define glDeleteShader nova_glDeleteShader

typedef GLuint (*PFNGLCREATEPROGRAMPROC)(void);
extern PFNGLCREATEPROGRAMPROC nova_glCreateProgram;
#define glCreateProgram nova_glCreateProgram

typedef void (*PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
extern PFNGLATTACHSHADERPROC nova_glAttachShader;
#define glAttachShader nova_glAttachShader

typedef void (*PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar* name);
extern PFNGLBINDATTRIBLOCATIONPROC nova_glBindAttribLocation;
#define glBindAttribLocation nova_glBindAttribLocation

typedef void (*PFNGLLINKPROGRAMPROC)(GLuint program);
extern PFNGLLINKPROGRAMPROC nova_glLinkProgram;
#define glLinkProgram nova_glLinkProgram

typedef void (*PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
extern PFNGLGETPROGRAMIVPROC nova_glGetProgramiv;
#define glGetProgramiv nova_glGetProgramiv

typedef void (*PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
extern PFNGLGETPROGRAMINFOLOGPROC nova_glGetProgramInfoLog;
#define glGetProgramInfoLog nova_glGetProgramInfoLog

typedef void (*PFNGLDELETEPROGRAMPROC)(GLuint program);
extern PFNGLDELETEPROGRAMPROC nova_glDeleteProgram;
#define glDeleteProgram nova_glDeleteProgram

typedef void (*PFNGLUSEPROGRAMPROC)(GLuint program);
extern PFNGLUSEPROGRAMPROC nova_glUseProgram;
#define glUseProgram nova_glUseProgram

typedef GLint (*PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar* name);
extern PFNGLGETUNIFORMLOCATIONPROC nova_glGetUniformLocation;
#define glGetUniformLocation nova_glGetUniformLocation

typedef void (*PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
extern PFNGLUNIFORM1IPROC nova_glUniform1i;
#define glUniform1i nova_glUniform1i

typedef void (*PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat* value);
extern PFNGLUNIFORM2FVPROC nova_glUniform2fv;
#define glUniform2fv nova_glUniform2fv

typedef void (*PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat* value);
extern PFNGLUNIFORM4FVPROC nova_glUniform4fv;
#define glUniform4fv nova_glUniform4fv

typedef void (*PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
extern PFNGLGENBUFFERSPROC nova_glGenBuffers;
#define glGenBuffers nova_glGenBuffers

typedef void (*PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
extern PFNGLBINDBUFFERPROC nova_glBindBuffer;
#define glBindBuffer nova_glBindBuffer

typedef void (*PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
extern PFNGLBUFFERDATAPROC nova_glBufferData;
#define glBufferData nova_glBufferData

typedef void (*PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
extern PFNGLBUFFERSUBDATAPROC nova_glBufferSubData;
#define glBufferSubData nova_glBufferSubData

typedef void (*PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint* buffers);
extern PFNGLDELETEBUFFERSPROC nova_glDeleteBuffers;
#define glDeleteBuffers nova_glDeleteBuffers

typedef void (*PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
extern PFNGLGENVERTEXARRAYSPROC nova_glGenVertexArrays;
#define glGenVertexArrays nova_glGenVertexArrays

typedef void (*PFNGLBINDVERTEXARRAYPROC)(GLuint array);
extern PFNGLBINDVERTEXARRAYPROC nova_glBindVertexArray;
#define glBindVertexArray nova_glBindVertexArray

typedef void (*PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint* arrays);
extern PFNGLDELETEVERTEXARRAYSPROC nova_glDeleteVertexArrays;
#define glDeleteVertexArrays nova_glDeleteVertexArrays

typedef void (*PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
extern PFNGLVERTEXATTRIBPOINTERPROC nova_glVertexAttribPointer;
#define glVertexAttribPointer nova_glVertexAttribPointer

typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
extern PFNGLENABLEVERTEXATTRIBARRAYPROC nova_glEnableVertexAttribArray;
#define glEnableVertexAttribArray nova_glEnableVertexAttribArray

typedef void (*PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC nova_glDisableVertexAttribArray;
#define glDisableVertexAttribArray nova_glDisableVertexAttribArray

typedef void (*PFNGLACTIVETEXTUREPROC)(GLenum texture);
extern PFNGLACTIVETEXTUREPROC nova_glActiveTexture;
#define glActiveTexture nova_glActiveTexture

typedef void (*PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
extern PFNGLBLENDFUNCSEPARATEPROC nova_glBlendFuncSeparate;
#define glBlendFuncSeparate nova_glBlendFuncSeparate

typedef void (*PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
extern PFNGLSTENCILOPSEPARATEPROC nova_glStencilOpSeparate;
#define glStencilOpSeparate nova_glStencilOpSeparate

typedef void (*PFNGLGENERATEMIPMAPPROC)(GLenum target);
extern PFNGLGENERATEMIPMAPPROC nova_glGenerateMipmap;
#define glGenerateMipmap nova_glGenerateMipmap

typedef GLuint (*PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar* uniformBlockName);
extern PFNGLGETUNIFORMBLOCKINDEXPROC nova_glGetUniformBlockIndex;
#define glGetUniformBlockIndex nova_glGetUniformBlockIndex

typedef void (*PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
extern PFNGLUNIFORMBLOCKBINDINGPROC nova_glUniformBlockBinding;
#define glUniformBlockBinding nova_glUniformBlockBinding

typedef void (*PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
extern PFNGLBINDBUFFERBASEPROC nova_glBindBufferBase;
#define glBindBufferBase nova_glBindBufferBase

typedef void (*PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
extern PFNGLBINDBUFFERRANGEPROC nova_glBindBufferRange;
#define glBindBufferRange nova_glBindBufferRange

// À appeler une fois, juste après avoir rendu le contexte GL courant
// (glfwMakeContextCurrent). Retourne 0 si une fonction requise n'a pas
// été trouvée (carte/driver trop ancien, ou erreur de chargement).
int nova_gl_lite_init(void);

#ifdef __cplusplus
}
#endif

#endif // NOVA_GL_LITE_H
