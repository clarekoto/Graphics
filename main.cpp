#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include "shader.h"

float squareVertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
}; 

float triVertices[] = {
    0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
    -0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Project1", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // glViewport(0, 0, 640, 800); don't need since framebuffer_size_callback does it
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    Shader shader("vertex.glsl", "fragment.glsl");

    // Element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    unsigned int VAO, VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // glm::mat4 transform = glm::mat4(1.0f);
    // transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    // transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));

    
    while (!glfwWindowShouldClose(window)) {
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        
        shader.use();
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        // float time = glfwGetTime();
        // float greenValue = (sin(time) / 2.0f) + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "uniColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}