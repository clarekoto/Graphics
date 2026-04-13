#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include "shader.h"

int WND_WIDTH = 1280;
int WND_HEIGHT = 960;

float squareVertices[] = {
    // back face - deep blue
    -0.5f, -0.5f, -0.5f,  0.0f, 0.2f, 0.8f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.2f, 0.8f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.2f, 0.8f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.2f, 0.8f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.2f, 0.8f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.2f, 0.8f,

    // front face - cyan
    -0.5f, -0.5f,  0.5f,  0.0f, 0.9f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.9f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.9f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.9f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.9f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.9f, 1.0f,

    // left face - purple
    -0.5f,  0.5f,  0.5f,  0.6f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.6f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.6f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.6f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.6f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.6f, 0.0f, 1.0f,

    // right face - violet
     0.5f,  0.5f,  0.5f,  0.8f, 0.2f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.8f, 0.2f, 1.0f,

    // bottom face - dark blue
    -0.5f, -0.5f, -0.5f,  0.0f, 0.1f, 0.5f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.1f, 0.5f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.1f, 0.5f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.1f, 0.5f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.1f, 0.5f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.1f, 0.5f,

    // top face - bright cyan
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.9f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.9f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.9f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.9f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.9f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.9f
};

float triVertices[] = {
    0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
    -0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    const int NUM_STARS = 400;
    glm::vec3 starPositions[NUM_STARS];
    srand(42); // fixed seed so stars don't move on restart
    for (int i = 0; i < NUM_STARS; i++) {
        starPositions[i] = glm::vec3(
            ((rand() % 200) - 100.0f),  // x: -100 to 100
            ((rand() % 200) - 100.0f),  // y: -100 to 100
            ((rand() % 200) - 100.0f)   // z: -100 to 100
        );
    }
    GLFWwindow* window = glfwCreateWindow(WND_WIDTH, WND_HEIGHT, "Project1", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);


    glEnable(GL_DEPTH_TEST); 
    shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WND_WIDTH / (float)WND_HEIGHT, 0.1f, 200.0f);
    shader.setMat4("projection", projection);

    while (!glfwWindowShouldClose(window)) {
        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

       
        glm::mat4 view = glm::mat4(1.0f);
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.5f));

        shader.setMat4("view", view);
        glBindVertexArray(VAO);
        shader.setFloat("alpha", 1.0f);

         // draw stars
        for (int i = 0; i < NUM_STARS; i++) {
            glm::mat4 starModel = glm::mat4(1.0f);
            starModel = glm::translate(starModel, starPositions[i]);
            starModel = glm::scale(starModel, glm::vec3(0.1f)); // tiny
            shader.setMat4("model", starModel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        

        glBindVertexArray(VAO);
    
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  0.0f));
        float angle = 20.0f; 
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader.setMat4("model", model);
        
        shader.setFloat("alpha", 1.0f);
        shader.setMat4("model", model);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        float offset = 0.002f;
        glm::vec3 offsets[] = {
            {0, 0, 0},
            {offset, 0, 0}, {-offset, 0, 0},
            {0, offset, 0}, {0, -offset, 0},
            {offset, offset, 0}, {-offset, -offset, 0},
            {offset, -offset, 0}, {-offset, offset, 0},
            {offset*2, 0, 0}, {-offset*2, 0, 0},
            {0, offset*2, 0}, {0, -offset*2, 0},
            {offset*2, offset*2, 0}, {-offset*2, -offset*2, 0},
            {offset*2, -offset*2, 0}, {-offset*2, offset*2, 0}
        };
        for (auto& o : offsets) {
            glm::mat4 offsetModel = model;
            offsetModel = glm::translate(offsetModel, o);
            shader.setMat4("model", offsetModel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}