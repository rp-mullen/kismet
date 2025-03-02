#include "ImGuiViewport.h"
#include <cstdio> // For printf
#include <iostream>
#include "Global.h"

IGViewport::IGViewport(int width, int height)
   : fbo(0), texture(0), rbo(0), size(width, height), show(true)
   {
   createFramebuffer(width, height);
   }

IGViewport::~IGViewport()
   {
   deleteFramebuffer();
   }

void IGViewport::createFramebuffer(int width, int height)
   {
   deleteFramebuffer(); // Ensure old framebuffer is cleaned up

   // Generate framebuffer
   glGenFramebuffers(1, &fbo);
   glBindFramebuffer(GL_FRAMEBUFFER, fbo);

   // Create color attachment texture
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

   // Create depth and stencil renderbuffer
   glGenRenderbuffers(1, &rbo);
   glBindRenderbuffer(GL_RENDERBUFFER, rbo);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

   // Check framebuffer completeness
   if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      {
      std::cerr << "ERROR: Framebuffer is not complete!\n";
      }

   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   }

void IGViewport::deleteFramebuffer()
   {
   if (texture) glDeleteTextures(1, &texture);
   if (rbo) glDeleteRenderbuffers(1, &rbo);
   if (fbo) glDeleteFramebuffers(1, &fbo);
   }

bool IGViewport::begin(const std::string& name)
   {
   return ImGui::Begin(name.c_str(), &show,
      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
   }

void IGViewport::renderScene(Scene& s)
   {
   glBindFramebuffer(GL_FRAMEBUFFER, fbo);
   glViewport(0, 0, (int)size.x, (int)size.y);
   glClearColor(s.backgroundColor.r,s.backgroundColor.g,s.backgroundColor.b,1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   s.render(Global::getInstance()->window);

   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   }

void IGViewport::update(Scene& s)
   {
   if (texture == 0) {
      std::cerr << "ERROR: Viewport texture not initialized!" << std::endl;
      abort();
      }

   if (show)
      {
      if (!begin("Viewport"))
         {
         ImGui::End();
         return;
         }

      // Resize framebuffer if needed
      ImVec2 newSize(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
      if (size.x != newSize.x || size.y != newSize.y)
         {
         size = newSize;
         createFramebuffer((int)size.x, (int)size.y);
         }

      renderScene(s);

      // Display the rendered texture in ImGui
      ImGui::Image((ImTextureID)(uintptr_t)texture, size, ImVec2(0, 1), ImVec2(1, 0));


      ImGui::End();
      }
   }
