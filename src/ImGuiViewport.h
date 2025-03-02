#ifndef IG_VIEWPORT_H
#define IG_VIEWPORT_H

#include "imgui.h"
#include <glad/glad.h>
#include <string>
#include "Scene.h"

class IGViewport
   {
   public:
      IGViewport(int width, int height);
      ~IGViewport();

      void update(Scene& s);
      bool begin(const std::string& name);

   private:
      void createFramebuffer(int width, int height);
      void deleteFramebuffer();
      void renderScene(Scene& s); // Placeholder for OpenGL rendering

      GLuint fbo, texture, rbo;
      ImVec2 size;
      bool show;
   };

#endif // IMGUI_VIEWPORT_H
