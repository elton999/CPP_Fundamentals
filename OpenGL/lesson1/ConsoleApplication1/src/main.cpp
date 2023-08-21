#include <iostream>
#include <sstream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"

const char* APP_TITLE = "Introduction to Modern OpenGL - Hello Shader";
int gWindowWidth = 1024;
int gWindowHeight = 768;
GLFWwindow* gWindow = NULL;
bool gWireframe = false;
bool gFullScreen = false;

OrbitCamera orbtiCamera;
float gYaw = 0.0f;
float gPitch = 0.0f;
float gRadius = 10.0f;
const float MOUSE_SENSITIVITY = 0.25f;

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_OnFrameBufferSize(GLFWwindow* window, int width, int height);
void glfw_OnMouseMove(GLFWwindow* window, double posX, double posY);
void showFPS(GLFWwindow* window);
bool InitOpenGL();

int main()
{
    if (!InitOpenGL())
    {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }

    GLfloat vert_pos[]
    {
        // position		 // tex coords

       // front face
       -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
       -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
       -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

        // back face
        -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

         // left face
         -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
         -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
         -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
         -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
         -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
         -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

         // right face
          1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
          1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
          1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
          1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
          1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
          1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

          // top face
         -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
          1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
          1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
         -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
         -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
          1.0f,  1.0f,  1.0f, 1.0f, 0.0f,

          // bottom face
         -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
          1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
          1.0f, -1.0f,  1.0f, 1.0f, 1.0f,
         -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
         -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
          1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
    };

    glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, -5.0f);

    GLuint vbo, vao;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_pos), vert_pos, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);

    // tex coord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLfloat*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    ShaderProgram shaderProgram;
    shaderProgram.loadShaders("basic.vert", "basic.frag");

    Texture2D texture1;
    texture1.loadTexture("wooden_crate.jpg", true);

    float cubeAngle = 0.0f;
    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(gWindow))
    {
        showFPS(gWindow);

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture1.bind(0);

        glm::mat4 model, view, projection;

        orbtiCamera.setLookAt(cubePos);
        orbtiCamera.rotate(gYaw, gPitch);
        orbtiCamera.setRadious(gRadius);

        model = glm::translate(model, cubePos);
        view = orbtiCamera.GetViewMatrix();
        projection = glm::perspective(glm::radians(45.0f), (float)gWindowWidth / (float)gWindowHeight, 0.1f, 100.0f);
        
        shaderProgram.use();
        shaderProgram.setUniform("model", model);
        shaderProgram.setUniform("view", view);
        shaderProgram.setUniform("projection", projection);

        glUniform1i(glGetUniformLocation(shaderProgram.getProgram(), "myTexture1"), 0);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(gWindow);

        lastTime = currentTime;
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
    return 0;
}

bool InitOpenGL()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    if (gFullScreen)
    {
        GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* pVmode = glfwGetVideoMode(pMonitor);
        if (pVmode != NULL)
            gWindow = glfwCreateWindow(pVmode->width, pVmode->height, APP_TITLE, pMonitor, NULL);
    }
    else
        gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);

    if (gWindow == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(gWindow);

    glfwSetKeyCallback(gWindow, glfw_onKey);
    glfwSetCursorPosCallback(gWindow, glfw_OnMouseMove);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to create GLEW window" << std::endl;
        return false;
    }

    glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
    glViewport(0, 0, gWindowWidth, gWindowHeight);
    glEnable(GL_DEPTH_TEST); // to add depth in the render.

    return true;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        gWireframe = !gWireframe;

        if (gWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void glfw_OnFrameBufferSize(GLFWwindow* window, int width, int height)
{
    gWindowWidth = width;
    gWindowHeight = height;
    glViewport(0, 0, gWindowWidth, gWindowHeight);
}

void glfw_OnMouseMove(GLFWwindow* window, double posX, double posY)
{
    static glm::vec2 lastMousePos = glm::vec2(0, 0);

    if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_LEFT) == 1)
    {
        gYaw -= ((float)posX - lastMousePos.x) * MOUSE_SENSITIVITY;
        gPitch += ((float)posY - lastMousePos.y) * MOUSE_SENSITIVITY;
    }

    if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_RIGHT) == 1)
    {
        float dx = 0.01f * ((float)posX - lastMousePos.x);
        float dy = 0.01f * ((float)posY - lastMousePos.y);
        gRadius += dx - dy;
    }

    lastMousePos.x = (float)posX;
    lastMousePos.y = (float)posY;
}

void showFPS(GLFWwindow* window)
{
    static double previousSecond = 0.0;
    static int frameCount = 0;
    double elapsedSecond;
    double currentSeconds = glfwGetTime();

    elapsedSecond = currentSeconds - previousSecond;

    if (elapsedSecond > 0.25)
    {
        previousSecond = currentSeconds;
        double fps = (double)frameCount / elapsedSecond;
        double msPerFrame = 1000.0 / fps;

        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed
            << APP_TITLE << "   "
            << "FPS: " << fps << "   "
            << "Frame Time: " << msPerFrame << " (ms)";
        glfwSetWindowTitle(window, outs.str().c_str());

        frameCount = 0;
    }

    frameCount++;
}