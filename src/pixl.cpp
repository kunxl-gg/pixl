#include "pixl/src/core/debug-console.hpp"
#include "pixl/src/core/debug.hpp"
#include "pixl/src/core/frame-buffer.hpp"
#include "pixl/src/core/model.hpp"
#include "pixl/src/pixl-precomp.hpp"

#include "pixl/src/core/shaders.hpp"
#include "pixl/src/core/camera.hpp"
#include "pixl/src/core/texture.hpp"
#include "pixl/src/core/vertex-array.hpp"
#include "pixl/src/core/vertex-buffer.hpp"

#include "pixl/src/editor/editor.hpp"

void checkError() {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }
}

bool blingPhong = false;

void processInput(GLFWwindow *window, pixl::Camera &camera) {
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboard(pixl::CameraMovement::kForward);
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboard(pixl::CameraMovement::kBackward);
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboard(pixl::CameraMovement::kLeft);
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboard(pixl::CameraMovement::kRight);
    } else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        blingPhong = !blingPhong;
    }
}

int main() {
    // Initialise GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Get the window height and width
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    const int WIDTH = mode->width;
    const int HEIGHT = mode->height;

    // Creat a window object
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Pixl", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make window the current context
    glfwMakeContextCurrent(window);

    // Load Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to load glad");
        return -1;
    }

    // Print the OpenGL version
    pixl::debug("OpenGL Version: %s", glGetString(GL_VERSION));
    pixl::debug("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    pixl::debug("Renderer: %s", glGetString(GL_RENDERER));
    pixl::debug("Vendor: %s", glGetString(GL_VENDOR));

    glm::vec3 cameraPos = glm::vec3(0.0, 0.5, 1.0);  // Camera position
    glm::vec3 cameraFront = glm::vec3(0.0, -0.1, -1.0);  // Looking down at the origin
    glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);  // Up direction

    pixl::Camera camera = pixl::Camera(cameraPos, cameraFront, cameraUp);
    glm::vec3 lightPos = glm::vec3(0.2f, 0.5f, 0.0f);

    float surf[] = {
        -0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  0.0f,  // Bottom-left
         0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f, 100.0f,  0.0f,  // Bottom-right
         0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 100.0f, 100.0f, // Top-right
         0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 100.0f, 100.0f, // Top-right (duplicate for triangle)
        -0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 100.0f,  // Top-left
        -0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  0.0f,  // Bottom-left (duplicate for triangle)
    };

    float vertices[] = {
        // positions         // normals          // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f
    };

    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Generating the Vertex Array Buffer
    pixl::VertexArray varrayBuffer;
    varrayBuffer.bind();

    // Generating the Vertex Buffer
    pixl::VertexBuffer vbuffer;
    vbuffer.bind(GL_ARRAY_BUFFER);
    vbuffer.setData(GL_ARRAY_BUFFER, sizeof(surf), surf);

    // Specify the vertex attributes
    varrayBuffer.setAttrib(0, 3, 8 * sizeof(float), 0);
    varrayBuffer.setAttrib(1, 3, 8 * sizeof(float), 3 * sizeof(float));
    varrayBuffer.setAttrib(2, 2, 8 * sizeof(float), 6 * sizeof(float));

    // Unbind all the vertex and element buffer objects
    vbuffer.unbind(GL_ARRAY_BUFFER);
    varrayBuffer.unbind();

    // Generate Vertex Buffers for light source
    pixl::VertexArray lightSourceVArrayBuffer;
    lightSourceVArrayBuffer.bind();

    pixl::VertexBuffer lightSourceVBuffer;
    lightSourceVBuffer.setData(GL_ARRAY_BUFFER, sizeof(vertices), vertices);

    varrayBuffer.setAttrib(0, 3, 8 * sizeof(float), 0);
    varrayBuffer.setAttrib(1, 3, 8 * sizeof(float), 3 * sizeof(float));
    varrayBuffer.setAttrib(2, 2, 8 * sizeof(float), 6 * sizeof(float));

    // Unbind all the vertex and element buffer objects
    lightSourceVBuffer.unbind(GL_ARRAY_BUFFER);
    lightSourceVArrayBuffer.unbind();

    // Compiling our shader
    std::string vShaderPath = std::filesystem::absolute("src/shaders/vert.glsl");
    std::string fShaderPath = std::filesystem::absolute("src/shaders/frag.glsl");
    pixl::Shader shader = pixl::Shader(vShaderPath, fShaderPath);

    // Sending uniforms
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(100.0f, 1.0f, 100.0f));
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    shader.use();

    shader.setMat4("model", model);
    shader.setMat4("projection", projection);

    shader.setVec3("lightPos", lightPos);
    shader.setVec3("viewPos", camera.getCameraPos());
    shader.setBool("blingPhong", blingPhong);

    // Compiling the light source shaders
    std::string vLightShader = std::filesystem::absolute("src/shaders/lvert.glsl");
    std::string fLightShader = std::filesystem::absolute("src/shaders/lfrag.glsl");
    pixl::Shader lightShader = pixl::Shader(vLightShader, fLightShader);

    lightShader.use();

    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    lightShader.setMat4("model", model);
    lightShader.setMat4("projection", projection);

    pixl::Texture texture = pixl::Texture(std::filesystem::absolute("assets/wood-surf.jpeg"), pixl::kDiffuse);
    texture.unbind();

    // Model shader
    std::string vModelShader = std::filesystem::absolute("src/shaders/mvert.glsl");
    std::string vFragShader = std::filesystem::absolute("src/shaders/mfrag.glsl");
    pixl::Shader modelShader = pixl::Shader(vModelShader, vFragShader);

    modelShader.use();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.2f, 0.2f, 0.0f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2.0f));
    modelShader.setMat4("model", model);
    modelShader.setMat4("projection", projection);

    glEnable(GL_DEPTH_TEST);


    float screen[] = {
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // Bottom-right
         0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  // Top-right
         0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  // Top-right (duplicate for triangle)
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // Top-left
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left (duplicate for triangle)
    };

    // Screen Buffer
    pixl::VertexArray sArray;
    pixl::VertexBuffer sBuffer;
    sArray.bind();

    sBuffer.bind(GL_ARRAY_BUFFER);
    sBuffer.setData(GL_ARRAY_BUFFER, sizeof(screen), screen);

    // Specify the vertex attributes
    sArray.setAttrib(0, 3, 8 * sizeof(float), 0);
    sArray.setAttrib(1, 3, 8 * sizeof(float), 3 * sizeof(float));
    sArray.setAttrib(2, 2, 8 * sizeof(float), 6 * sizeof(float));

    // Unbind all the vertex and element buffer objects
    sBuffer.unbind(GL_ARRAY_BUFFER);
    sArray.unbind();

    pixl::FrameBuffer frameBuffer = pixl::FrameBuffer();
    frameBuffer.create(mode->width, mode->height);
    frameBuffer.bind();

    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mode->width, mode->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (!frameBuffer.isComplete()) {
        pixl::error("Framebuffer is not complete!");
    } else {
        pixl::info("Framebuffer is complete!");
    }
    frameBuffer.unbind();

    pixl::Shader screenShader = pixl::Shader("src/shaders/svert.glsl", "src/shaders/sfrag.glsl");

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Process Inputs
        glfwPollEvents();
        processInput(window, camera);

        frameBuffer.bind();
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = camera.getViewMatrix();
        texture.bind();

        shader.use();
        shader.setMat4("view", view);
        shader.setInt("blingPhong", blingPhong);

        varrayBuffer.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        texture.unbind();

        lightShader.use();
        lightShader.setMat4("view", view);

        lightSourceVArrayBuffer.bind();
        glDrawArrays(GL_TRIANGLES, 0, 54);
        glBindVertexArray(0);

        frameBuffer.unbind();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool p_open = true;
        pixl::ShowExampleAppDockSpace(&p_open, textureColorbuffer);
        /*
        modelShader.use();
        modelShader.setMat4("view", view);
        ourModel.drawModel(modelShader);
         * */

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
