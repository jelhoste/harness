// Nova — harnais de développement, étape 2
// Objectif de cette étape : faire tourner NanoVG au-dessus de GLFW, avec
// notre loader OpenGL maison (gl_lite), et dessiner une forme de test pour
// prouver que toute la chaîne de rendu fonctionne.

#include "gl_lite.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>

#include <cstdio>

static void glfw_error_callback(int error, const char* description)
{
    std::fprintf(stderr, "[GLFW error %d] %s\n", error, description);
}

int main()
{
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
        std::fprintf(stderr, "Échec de glfwInit()\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(1024, 700, "Nova — harnais de dev (étape 2 : NanoVG)", nullptr, nullptr);
    if (!window)
    {
        std::fprintf(stderr, "Échec de glfwCreateWindow()\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!nova_gl_lite_init())
    {
        std::fprintf(stderr, "Échec du chargement des fonctions OpenGL — voir les symboles manquants ci-dessus.\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    if (!vg)
    {
        std::fprintf(stderr, "Échec de nvgCreateGL3() — le contexte NanoVG n'a pas pu être créé.\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        int winWidth, winHeight;
        glfwGetWindowSize(window, &winWidth, &winHeight);

        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

        float pixelRatio = (winWidth > 0) ? (float)fbWidth / (float)winWidth : 1.0f;

        glViewport(0, 0, fbWidth, fbHeight);
        glClearColor(0.12f, 0.12f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        nvgBeginFrame(vg, (float)winWidth, (float)winHeight, pixelRatio);

        // Forme de test : un rectangle arrondi, pour valider tout le
        // pipeline (shaders compilés, buffers, anti-aliasing NanoVG).
        nvgBeginPath(vg);
        nvgRoundedRect(vg, 100, 100, 300, 160, 16);
        nvgFillColor(vg, nvgRGBA(80, 160, 220, 255));
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgRoundedRect(vg, 100, 100, 300, 160, 16);
        nvgStrokeColor(vg, nvgRGBA(255, 255, 255, 200));
        nvgStrokeWidth(vg, 2.0f);
        nvgStroke(vg);

        nvgEndFrame(vg);

        glfwSwapBuffers(window);
    }

    nvgDeleteGL3(vg);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
