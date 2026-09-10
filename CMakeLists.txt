cmake_minimum_required(VERSION 3.16)
project(nova_harness LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
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

# On désactive le backend Wayland : l'outil wayland-scanner requis pour le
# compiler n'est pas présent par défaut sur les runners CI, et X11 seul
# suffit largement pour notre usage (plugin audio, pas de session Wayland
# pure à supporter en priorité).
set(GLFW_BUILD_WAYLAND  OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# --- NanoVG (source officielle, pas de CMake fourni en amont donc on
#     déclare nous-mêmes une petite lib statique à partir de ses sources) --
FetchContent_Declare(
    nanovg
    GIT_REPOSITORY https://github.com/memononen/nanovg.git
)
FetchContent_MakeAvailable(nanovg)

add_library(nanovg STATIC
    ${nanovg_SOURCE_DIR}/src/nanovg.c
)
target_include_directories(nanovg PUBLIC ${nanovg_SOURCE_DIR}/src)

# --- Clay (layout, header unique) -----------------------------------------
FetchContent_Declare(
    clay
    GIT_REPOSITORY https://github.com/nicbarker/clay.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(clay)

# --- Exécutable ----------------------------------------------------------
add_executable(nova_harness
    src/main.cpp
    src/gl_lite.c
    src/clay_impl.cpp
    src/clay_nanovg_renderer.cpp
)

target_include_directories(nova_harness PRIVATE ${clay_SOURCE_DIR})

target_link_libraries(nova_harness PRIVATE glfw nanovg)

if(UNIX AND NOT APPLE)
    target_link_libraries(nova_harness PRIVATE m)
endif()

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
