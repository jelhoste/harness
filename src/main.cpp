// Nova — harnais de développement, étape 3
// Objectif de cette étape : brancher Clay (layout) au-dessus de NanoVG
// (dessin) et GLFW (fenêtre), pour afficher une mise en page de test
// (un bandeau + deux panneaux) calculée par Clay et dessinée par NanoVG.

#include "gl_lite.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>

#include "clay.h"
#include "clay_nanovg_renderer.h"

#include <cstdio>
#include <cstdlib>

static void glfw_error_callback(int error, const char* description)
{
    std::fprintf(stderr, "[GLFW error %d] %s\n", error, description);
}

static void nova_clay_error_handler(Clay_ErrorData errorData)
{
    std::fprintf(stderr, "[Clay] %.*s\n", errorData.errorText.length, errorData.errorText.chars);
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

    GLFWwindow* window = glfwCreateWindow(1024, 700, "Nova — harnais de dev (étape 3 : Clay)", nullptr, nullptr);
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

    // --- Initialisation de Clay --------------------------------------
    uint32_t clayMemSize = Clay_MinMemorySize();
    void* clayMemory = std::malloc(clayMemSize);
    Clay_Arena clayArena = Clay_CreateArenaWithCapacityAndMemory(clayMemSize, clayMemory);

    int initWidth, initHeight;
    glfwGetWindowSize(window, &initWidth, &initHeight);

    Clay_ErrorHandler errorHandler;
    errorHandler.errorHandlerFunction = nova_clay_error_handler;
    errorHandler.userData = 0;

    Clay_Dimensions initDims = { (float)initWidth, (float)initHeight };
    Clay_Initialize(clayArena, initDims, errorHandler);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        int winWidth, winHeight;
        glfwGetWindowSize(window, &winWidth, &winHeight);

        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

        float pixelRatio = (winWidth > 0) ? (float)fbWidth / (float)winWidth : 1.0f;

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        bool mouseDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

        // --- Layout (Clay) ---------------------------------------------
        Clay_Dimensions frameDims = { (float)winWidth, (float)winHeight };
        Clay_SetLayoutDimensions(frameDims);

        Clay_Vector2 pointerPos = { (float)mouseX, (float)mouseY };
        Clay_SetPointerState(pointerPos, mouseDown);

        float deltaTime = 0.016f;
        Clay_Vector2 scrollDelta = { 0, 0 };
        Clay_UpdateScrollContainers(false, scrollDelta, deltaTime);

        Clay_BeginLayout();

        CLAY(CLAY_ID("Root"),
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                .padding = CLAY_PADDING_ALL(16),
                .childGap = 16,
                .layoutDirection = CLAY_TOP_TO_BOTTOM
            },
            .backgroundColor = { 24, 24, 27, 255 }
        ) {
            CLAY(CLAY_ID("Header"),
                .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(56) } },
                .backgroundColor = { 70, 120, 180, 255 },
                .cornerRadius = CLAY_CORNER_RADIUS(8)
            ) {}

            CLAY(CLAY_ID("Body"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .childGap = 16,
                    .layoutDirection = CLAY_LEFT_TO_RIGHT
                }
            ) {
                CLAY(CLAY_ID("LeftPanel"),
                    .layout = { .sizing = { CLAY_SIZING_FIXED(220), CLAY_SIZING_GROW(0) } },
                    .backgroundColor = { 45, 45, 52, 255 },
                    .cornerRadius = CLAY_CORNER_RADIUS(8)
                ) {}

                CLAY(CLAY_ID("RightPanel"),
                    .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) } },
                    .backgroundColor = { 38, 38, 44, 255 },
                    .cornerRadius = CLAY_CORNER_RADIUS(8)
                ) {}
            }
        }

        Clay_RenderCommandArray clayCommands = Clay_EndLayout(deltaTime);

        // --- Rendu (NanoVG) ----------------------------------------------
        glViewport(0, 0, fbWidth, fbHeight);
        glClearColor(0.09f, 0.09f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        nvgBeginFrame(vg, (float)winWidth, (float)winHeight, pixelRatio);
        nova_render_clay_commands(vg, clayCommands);
        nvgEndFrame(vg);

        glfwSwapBuffers(window);
    }

    std::free(clayMemory);
    nvgDeleteGL3(vg);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
