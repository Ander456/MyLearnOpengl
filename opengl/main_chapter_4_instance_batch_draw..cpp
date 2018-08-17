//
//  main.cpp
//  opengl
//
//  Created by Alex on 2018/4/4.
//  Copyright © 2018年 Alex. All rights reserved.
//

#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include "stb_image.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.hpp"
#include "Model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 55.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(int argc, const char * argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // for Mac OS X
    const char* ss = glfwGetVersionString();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glewExperimental = GL_TRUE;
    glewInit();

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    
//    glm::vec2 translations[100];
//    int index = 0;
//    float offset = 0.1f;
//    for (int y = -10; y < 10; y += 2)
//    {
//        for (int x = -10; x < 10; x += 2)
//        {
//            glm::vec2 translation;
//            translation.x = (float)x / 10.0f + offset;
//            translation.y = (float)y / 10.0f + offset;
//            translations[index++] = translation;
//        }
//    }
//
//    // store instance data in an array buffer
//    // --------------------------------------
//    unsigned int instanceVBO;
//    glGenBuffers(1, &instanceVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Model rock("path/rock/rock.obj");
    Model planet("path/planet/planet.obj");
    
//    Shader shader("path/instance.vs", "path/instance.fs");
    Shader asteroidShader("path/instance.vs", "path/instance.fs");
    Shader planetShader("path/planet.vs", "path/planet.fs");
    
//    for(unsigned int i = 0; i < 100; i++)
//    {
//        stringstream ss;
//        string index;
//        ss << i;
//        index = ss.str();
//        shader.setVec2(("offsets[" + index + "]").c_str(), translations[i]); // ，但是如果我们要渲染远超过100个实例的时候（这其实非常普遍），我们最终会超过最大能够发送至着色器的uniform数据大小上限。
//    }
    
//    float quadVertices[] = {
//        // 位置          // 颜色
//        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
//
//        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//        0.05f,  0.05f,  0.0f, 1.0f, 1.0f
//    };
//    unsigned int VBO, VAO;
//    glGenBuffers(1, &VBO);
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glVertexAttribDivisor(2, 1);

    
    unsigned int amount = 10000;
    glm::mat4* modelMatrices;
    modelMatrices = new glm::mat4[amount];
    srand(glfwGetTime()); // initialize random seed
    float radius = 150.0;
    float offset = 25.0f;
    for (unsigned int i = 0; i < amount; i++)
    {
        glm::mat4 model;
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));
        
        // 2. scale: Scale between 0.05 and 0.25f
        float scale = (rand() % 20) / 100.0f + 0.05;
        model = glm::scale(model, glm::vec3(scale));
        
        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
        
        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }
    
    // configure instanced array
    // -------------------------
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
    
    // set transformation matrices as an instance vertex attribute (with divisor 1)
    // note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
    // -----------------------------------------------------------------------------------------------------------------------------------
    for (unsigned int i = 0; i < rock.meshes.size(); i++)
    {
        unsigned int VAO = rock.meshes[i].VAO;
        glBindVertexArray(VAO);
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
        
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        
        glBindVertexArray(0);
    }

    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        processInput(window);
        
        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
//        shader.use();
//        glBindVertexArray(VAO);
//        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);

//        // configure transformation matrices
//        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
//        glm::mat4 view = camera.GetViewMatrix();;
//        shader.use();
//        shader.setMat4("projection", projection);
//        shader.setMat4("view", view);
//
//        // draw planet
//        glm::mat4 model;
//        model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
//        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
//        shader.setMat4("model", model);
//        planet.Draw(shader);
//
////        // draw meteorites
////        for (unsigned int i = 0; i < amount; i++)
////        {
////            shader.setMat4("model", modelMatrices[i]);
////            rock.Draw(shader);
////        }

        // configure transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        asteroidShader.use();
        asteroidShader.setMat4("projection", projection);
        asteroidShader.setMat4("view", view);
        planetShader.use();
        planetShader.setMat4("projection", projection);
        planetShader.setMat4("view", view);
        
        // draw planet
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        planetShader.setMat4("model", model);
        planet.Draw(planetShader);
        
        // draw meteorites
        asteroidShader.use();
        asteroidShader.setInt("texture_diffuse1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
        for (unsigned int i = 0; i < rock.meshes.size(); i++)
        {
            glBindVertexArray(rock.meshes[i].VAO);
            glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
            glBindVertexArray(0);
        }
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
