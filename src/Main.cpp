
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ImGuiUI.h"
#include "Global.h"
#include <iostream>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Model.h"
#include "Renderer.h"
#include "Scene.h"
#include "ImGuiViewport.h"
#include "UserControls.h"

#include <glm/ext/matrix_transform.hpp>
#include "GameObject.h" // Add this include to resolve the GameObject type


#include "ModelComponent.cpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
   glViewport(0, 0, width, height);
   }

int main() {
   if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW" << std::endl;
      return -1;
      }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL with ImGui", NULL, NULL);
   if (!window) {
      std::cerr << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
      }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD" << std::endl;
      return -1;
      }

   glEnable(GL_DEPTH_TEST);


   Global* global = Global::getInstance();
   global->window = window;

   UI ui(window);
    ModelComponent modelComponent(nullptr);
    Model model(&modelComponent, "C:\\Users\\rpm\\source\\repos\\3DEngine\\models\\goose.fbx");
   Renderer r;
   Light l(glm::vec3(0, -1, 0), glm::vec3(0, 0, 0), 1.0f, 1.0f, 0.09f, 0.032f); // Point light constructor
   Scene s(r);

   global->setScene(s);
   GameObject go;
   go.addComponent<ModelComponent>(model);
   go.addComponent<TransformComponent>();
   global->scene.addGameObject(go);
 

    // Existing code...
   global->scene.addLight(l);
   
   

   while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();

      

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

     
      glClearColor(0.0f,0.0f,0.0f,1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Render UI
      ui.renderUI(global->scene, window);

      UserControls::getInstance()->update(window);

      //// Render 3D Scene
      //global->scene.render(window);

      // End the current frame
      ImGui::EndFrame();   // This should be called at the end of your frame processing

      
      
      // Render and draw the frame
      ImGui::Render(); // Call ImGui render function
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Draw ImGui data with OpenGL

      // Swap buffers
      glfwSwapBuffers(window);
      }

   // Cleanup
   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();
   glfwDestroyWindow(window);
   glfwTerminate();
   return 0;
   }
