#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include "shader.h"
#include "model.h"
// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>



glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;
float lastX = 400, lastY = 300;
float fov   =  45.0f;
int SCR_WIDTH = 640;
int SCR_HEIGHT = 480;
int colourMode = 0;


float squareVertices[] = {
    // -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.1f,
    //  0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
    // -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    //  0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    //  0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    // -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

    // -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    // -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
    // -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,

    //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
    //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
    //  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
    //  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
    //  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
    //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,

    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
    //  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
    //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
    //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,1.0f,
    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f
};

float triVertices[] = {
    0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
    -0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void process_input(GLFWwindow* window) {
    const float speed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos +=  speed * cameraFront;
    } 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= speed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        colourMode = 1 - colourMode;
    }




}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}  

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Project1", NULL, NULL);
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
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // colour attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};


    const float radius = 10.0f;
    // stbi_set_flip_vertically_on_load(true);
    Model model("3d_models/1.obj");
    std::cout << "Meshes loaded: " << model.meshes.size() << std::endl;


    glEnable(GL_DEPTH_TEST); 
    shader.use();
    glm::mat4 view;
    glfwSetCursorPosCallback(window, mouse_callback); 
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 


    glm::mat4 projection = glm::perspective(glm::radians(35.0f), (float)640 / (float)480, 0.1f, 100.0f);
    shader.setMat4("projection", projection);
    while (!glfwWindowShouldClose(window)) {
         // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        process_input(window);

        // render
        // ------
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setInt("colourMode", colourMode);

        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        float t = (float)glfwGetTime();

        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::scale(modelMat, glm::vec3(0.001f));
        modelMat = glm::translate(modelMat, glm::vec3(sin(t) * 50.0f, 0.0f, 0.0f));
        modelMat = glm::rotate(modelMat, t * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", modelMat);

        model.Draw(shader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
