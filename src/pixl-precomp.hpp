#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "pixl/include/assimp/Importer.hpp"
#include "pixl/include/assimp/scene.h"
#include "pixl/include/assimp/postprocess.h"

#include "pixl/include/glad/glad.h"
#include "pixl/include/GLFW/glfw3.h"

#include "pixl/include/glm/glm.hpp"
#include "pixl/include/glm/gtc/type_ptr.hpp"

#include "pixl/include/imgui/imgui.h"
#include "pixl/include/imgui/imgui_internal.h"
#include "pixl/include/imgui/imgui_impl_glfw.h"
#include "pixl/include/imgui/imgui_impl_opengl3.h"

#include "pixl/src/core/debug.hpp"
