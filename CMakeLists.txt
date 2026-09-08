cmake_minimum_required(VERSION 3.16)
project(nova_harness LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# --- GLFW via FetchContent ---------------------------------------------
include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# --- Exécutable ----------------------------------------------------------
add_executable(nova_harness
    src/main.cpp
)

target_link_libraries(nova_harness PRIVATE glfw)

# --- OpenGL selon plateforme ----------------------------------------------
if(APPLE)
    target_link_libraries(nova_harness PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
elseif(UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(nova_harness PRIVATE OpenGL::GL)
elseif(WIN32)
    target_link_libraries(nova_harness PRIVATE opengl32)
endif()
