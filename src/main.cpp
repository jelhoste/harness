// Nova — harnais de développement, étape 1
// Objectif de cette étape : prouver que GLFW se compile et s'ouvre
// correctement sur les 3 OS, avant d'ajouter NanoVG puis Clay.

#include <GLFW/glfw3.h>
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

    // On demande un contexte OpenGL 3.2 Core (suffisant pour NanoVG GL3,
    // qu'on ajoutera à l'étape 2). Sur macOS, le forward-compat est requis.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(1024, 700, "Nova — harnais de dev", nullptr, nullptr);
    if (!window)
    {
        std::fprintf(stderr, "Échec de glfwCreateWindow()\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync — on affinera plus tard si besoin (basse latence)

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        glViewport(0, 0, fbWidth, fbHeight);

        // Couleur de fond neutre, provisoire — sera remplacée par le
        // rendu NanoVG/Clay à l'étape suivante.
        glClearColor(0.12f, 0.12f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
