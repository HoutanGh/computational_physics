#include <iostream>
#include <GLFW/glfw3.h>
#include <math.h>

float screenHeight = 600.0f;
float screenWidth = 800.0f;


GLFWwindow* StartGLFW();

int main() {
    GLFWwindow* window = StartGLFW();
    if (!window) return -1;

    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;
    float radius = 50.0f;
    int res = 100;

    glfwMakeContextCurrent(window);

    // Set up orthographic projection to use pixel coordinates
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(centerX, centerY);
        
        for (int i = 0; i <= res; ++i)  {
            float angle = 2.0f * M_PI * (static_cast<float>(i) / res);
            float x = centerX + cos(angle) * radius;
            float y = centerY + sin(angle) * radius;
            glVertex2d(x, y);
        }

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

GLFWwindow* StartGLFW() {
    if(!glfwInit()) {
        std::cerr << "failed to initialise GLFW\n" << std::endl;
        return nullptr;
    }
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "gravity_sim", NULL, NULL);

    return window;
}