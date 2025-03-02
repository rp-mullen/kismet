// Scene.cpp
#include "Scene.h"
#include "GameObject.h" // Add this include to resolve the incomplete type error
#include "ModelComponent.cpp"

Scene::Scene(Renderer& renderer)
  : camera(Camera(glm::vec3(0.0f, 0.0f, 5.0f))), renderer(renderer) {
  setup();
  }

void Scene::addGameObject(const GameObject& go) {  
  // Add the GameObject to the scene
  gameObjects.push_back(go);  
 
  // Dynamic cast to see if the GameObject is a Model
  if (auto modelComponent = const_cast<GameObject&>(go).getComponent<ModelComponent>()) { // Fix type name is not allowed error
     renderer.addModel(modelComponent->model);
  }
}

void Scene::removeGameObject(const GameObject& go) {
  gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), go), gameObjects.end());
  if (auto modelComponent = const_cast<GameObject&>(go).getComponent<ModelComponent>()) { // Fix type name is not allowed error
     renderer.removeModel(modelComponent->model);
  }
}
  

void Scene::removeGameObject(const GameObject& go) {
  gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), go), gameObjects.end());
  if (auto modelComponent = const_cast<GameObject&>(go).getComponent<ModelComponent>()) { // Fix type name is not allowed error
     renderer.removeModel(modelComponent->model);
     }
  }

void Scene::addLight(const Light& light) {
  lights.push_back(light);
  }

void Scene::removeLight(const Light& light) {
  lights.erase(std::remove(lights.begin(), lights.end(), light), lights.end());
  }

void Scene::setCamera(const Camera& camera) {
  this->camera = camera;
  }

void Scene::setup() {
     backgroundColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
     glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
     glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
     renderer.currentShader->setMat4("view", view);
     renderer.currentShader->setMat4("projection", projection);
  }

void Scene::render(GLFWwindow* window) {
  // Upload camera and global light properties
  float currentFrame = glfwGetTime();
  float deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  // Process keyboard input
  camera.ProcessKeyboard(window, deltaTime);

  // Process mouse movement
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  if (UserControls::getInstance()->controlState == CONTROL_STATE_VIEWPORT) {
        camera.ProcessMouseMovement(xpos - lastX, lastY - ypos, window, true);
     }
  glm::mat4 view = camera.getViewMatrix();
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  if (!renderer.currentShader) return;

  renderer.currentShader->use();
  renderer.currentShader->setMat4("view", view);
  renderer.currentShader->setMat4("projection", projection);

  // Set light properties
  for (size_t i = 0; i < lights.size(); ++i) {
     std::string lightName = "lights[" + std::to_string(i) + "].";
     lights[i].setLightProperties(*(renderer.currentShader), lightName);
     }

  // Render all models in the scene
  renderer.render();
  }
