#ifndef SCENE_H
#define SCENE_H

// Scene.h
#include <vector>
#include "Model.h"
#include "Light.h"
#include "Camera.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "UserControls.h"
class Scene {
public:
   std::vector<GameObject> gameObjects;   // Models in the scene
   std::vector<Light> lights;   // Lights in the scene
   Camera camera;               // Camera used for rendering
   Renderer& renderer;           // Renderer for handling drawing
   glm::vec4 backgroundColor;


   Scene() : renderer(*(new Renderer())) {
      backgroundColor = glm::vec4(0.0f);
      gameObjects = std::vector<GameObject>();
      lights = std::vector<Light>();
      camera = Camera();
      lastFrame = 0.0f;
      lastX = 400;
      lastY = 300;
   }
   Scene(Renderer& renderer);
   void addGameObject(const GameObject& go);
   void removeGameObject(const GameObject& go);
   void addLight(const Light& light);
   void removeLight(const Light& light);
   void setCamera(const Camera& camera);
   void render(GLFWwindow* window);

   void setup();

   Scene(const Scene& other) : backgroundColor(other.backgroundColor), gameObjects(other.gameObjects), lights(other.lights), camera(other.camera), renderer(other.renderer), lastFrame(other.lastFrame), lastX(other.lastX), lastY(other.lastY) {}

   Scene& operator=(const Scene& other) {
      if (this == &other)
         return *this;
      backgroundColor = other.backgroundColor;
      gameObjects = other.gameObjects;
      lights = other.lights;
      camera = other.camera;
      lastFrame = other.lastFrame;
      lastX = other.lastX;
      lastY = other.lastY;
      return *this;
      }

private:
   
   float lastFrame = 0.0f;
   float lastX = 400, lastY = 300;
   
   };

#endif