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

// --- Enums utilisés par NanoVG (backend GL3), absents des en-têtes 1.1 ---
#define GL_ARRAY_BUFFER                  0x8892
#define GL_ELEMENT_ARRAY_BUFFER          0x8893
#define GL_STREAM_DRAW                   0x88E0
#define GL_STATIC_DRAW                   0x88E4
#define GL_DYNAMIC_DRAW                  0x88E8
#define GL_FRAGMENT_SHADER               0x8B30
#define GL_VERTEX_SHADER                 0x8B31
#define GL_COMPILE_STATUS                0x8B81
#define GL_LINK_STATUS                   0x8B82
#define GL_INFO_LOG_LENGTH                0x8B84
#ifndef GL_TEXTURE0
#define GL_TEXTURE0                      0x84C0
#endif
#ifndef GL_RED
#define GL_RED                           0x1903
#endif
#define GL_TEXTURE_SWIZZLE_RGBA          0x8E46
#define GL_FRAMEBUFFER_SRGB              0x8DB9
#ifndef GL_UNIFORM_BUFFER
#define GL_UNIFORM_BUFFER                0x8A11
#endif
#ifndef GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE                 0x812F
#endif
#ifndef GL_INCR_WRAP
#define GL_INCR_WRAP                     0x8507
#endif
#ifndef GL_DECR_WRAP
#define GL_DECR_WRAP                     0x8508
#endif

// --- Pointeurs de fonctions -------------------------------------------
typedef GLuint (*PFNGLCREATESHADERPROC)(GLenum type);
typedef void (*PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
typedef void (*PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef void (*PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint* params);
typedef void (*PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
typedef void (*PFNGLDELETESHADERPROC)(GLuint shader);
typedef GLuint (*PFNGLCREATEPROGRAMPROC)(void);
typedef void (*PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (*PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar* name);
typedef void (*PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void (*PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
typedef void (*PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
typedef void (*PFNGLDELETEPROGRAMPROC)(GLuint program);
typedef void (*PFNGLUSEPROGRAMPROC)(GLuint program);
typedef GLint (*PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar* name);
typedef void (*PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
typedef void (*PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat* value);
typedef void (*PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat* value);

typedef void (*PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef void (*PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (*PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (*PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
typedef void (*PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint* buffers);

typedef void (*PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
typedef void (*PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (*PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint* arrays);

typedef void (*PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (*PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);

typedef void (*PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (*PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (*PFNGLGENERATEMIPMAPPROC)(GLenum target);
typedef GLuint (*PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar* uniformBlockName);
typedef void (*PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
typedef void (*PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
typedef void (*PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);

// glActiveTexture (OpenGL 1.3) est parfois déjà déclarée directement par
// l'en-tête système (observé sur Linux/Mesa) — dans ce cas on ne la
// redéclare pas, pour éviter un conflit de déclaration.
#ifndef GL_VERSION_1_3
typedef void (*PFNGLACTIVETEXTUREPROC)(GLenum texture);
#define NOVA_NEED_GLACTIVETEXTURE 1
#endif

extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;

extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;

extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

#ifdef NOVA_NEED_GLACTIVETEXTURE
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
#endif
extern PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
extern PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
extern PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
extern PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;
extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;
extern PFNGLBINDBUFFERRANGEPROC glBindBufferRange;

// À appeler une fois, juste après avoir rendu le contexte GL courant
// (glfwMakeContextCurrent). Retourne 0 si une fonction requise n'a pas
// été trouvée (carte/driver trop ancien, ou erreur de chargement).
int nova_gl_lite_init(void);

#ifdef __cplusplus
}
#endif

#endif // NOVA_GL_LITE_H
