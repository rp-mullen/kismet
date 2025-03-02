
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <vector>
#include "Model.h"
#include "Renderer.h"
#include "Scene.h"
#include "Global.h"

#include "ImGuiViewport.h"
#include "ImGuiMenubar.h"
#include "TransformComponent.cpp"


class UI {
public:

   IGViewport viewport;
   IGMenubar menubar;
   UI(GLFWwindow* window) : viewport(900,500) {
      initialize(window);
      }

   void initialize(GLFWwindow* window) {
      // Setup Dear ImGui
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
      ImGui::StyleColorsDark();
      ImGui_ImplGlfw_InitForOpenGL(window, true);
      ImGui_ImplOpenGL3_Init("#version 330");
      }
   
   void renderUI(Scene& s, GLFWwindow* window) {
      
      menubar.RenderMenuBar();
      RenderEditor();
      ShowModelInspector();
      viewport.update(s);   
      
      }



   void ShowModelInspector() {
      Global* global = Global::getInstance();
      if (global == nullptr) {
         ImGui::Text("Scene not loaded.");
         return;
         }

      // Create ImGui sidebar for model information
      ImGui::Begin("Inspector");

      // Check if models exist in the scene
      if (global->scene.renderer.models.empty()) {
         ImGui::Text("No models in the scene.");
         }
      else {
         std::vector<GameObject> models = global->findObjectsByComponent<Model>();
         // Display model information dynamically
         for (int i = 0; i < models.size(); ++i) {
            GameObject& model = models[i];

            std::string modelName = "Model " + std::to_string(i);
            ImGui::Text(modelName.c_str());

            // Model-specific information (e.g., position, scale, etc.)
           
                ImGui::DragFloat3(("Position##" + modelName).c_str(), &model.getComponent<TransformComponent>()->position[0], 0.1f);
                ImGui::DragFloat3(("Scale##" + modelName).c_str(), &model.getComponent<TransformComponent>()->scale[0], 0.1f);
                ImGui::DragFloat3(("Rotation##" + modelName).c_str(), &model.getComponent<TransformComponent>()->rotation[0], 0.1f);
            }
         }

      ImGui::End();
      }

private:
   GLuint framebuffer = 0;
   GLuint texture = 0;
   GLuint depthRenderbuffer = 0;

   void initializeFramebuffer(ImVec2 viewportSize) {
      glGenFramebuffers(1, &framebuffer);
      glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

      // Generate the texture to hold the rendered image
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLint>(viewportSize.x), static_cast<GLint>(viewportSize.y), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

      // Set texture parameters for the generated texture
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      // Attach the texture to the framebuffer
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

      // Generate and attach the depth renderbuffer
      glGenRenderbuffers(1, &depthRenderbuffer);
      glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, static_cast<GLint>(viewportSize.x), static_cast<GLint>(viewportSize.y));
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);

      // Check if the framebuffer is complete
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
         std::cerr << "Framebuffer is not complete!" << std::endl;
         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         return;
         }

      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }

   void RenderEditor()
      {
      static bool opt_fullscreen = true;
      static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

      ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
      if (opt_fullscreen)
         {
         ImGuiViewport* viewport = ImGui::GetMainViewport();
         ImGui::SetNextWindowPos(viewport->Pos);
         ImGui::SetNextWindowSize(viewport->Size);
         ImGui::SetNextWindowViewport(viewport->ID);
         window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
         window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
         }

      ImGui::Begin("DockSpace Demo", nullptr, window_flags);
      ImGui::DockSpace(ImGui::GetID("MainDockspace"));
      ImGui::End();
      }
   };
