#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
   // Camera attributes
   glm::vec3 position;
   glm::vec3 front;
   glm::vec3 up;
   glm::vec3 right;
   glm::vec3 worldUp;

   float yaw;
   float pitch;

   float movementSpeed;
   float mouseSensitivity = 0.1f;
   float zoom;

   // Constructor
   Camera(glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 startUp = glm::vec3(0.0f, 1.0f, 0.0f), float startYaw = -90.0f, float startPitch = 0.0f);

   // Get view matrix
   glm::mat4 getViewMatrix();

   // Get projection matrix
   glm::mat4 getProjectionMatrix(float width, float height);

   // Process keyboard input
   void ProcessKeyboard(GLFWwindow* window, float deltaTime);

   // Process mouse movement
   void ProcessMouseMovement(float xoffset, float yoffset, GLFWwindow* window, GLboolean constrainPitch);

   // Process mouse scroll
   void ProcessMouseScroll(float yoffset);

private:
   // Update the camera's front, right, and up vectors
   void updateCameraVectors();
   };

#endif