#include "Camera.h"

Camera::Camera(glm::vec3 startPos, glm::vec3 startUp, float startYaw, float startPitch)
   : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f)
   {
   position = startPos;
   worldUp = startUp;
   yaw = startYaw;
   pitch = startPitch;
   updateCameraVectors();
   }

glm::mat4 Camera::getViewMatrix() {
   return glm::lookAt(position, position + front, up);
   }

glm::mat4 Camera::getProjectionMatrix(float width, float height) {
   return glm::perspective(glm::radians(zoom), width / height, 0.1f, 100.0f);
   }

void Camera::ProcessKeyboard(GLFWwindow* window, float deltaTime) {
   float velocity = movementSpeed * deltaTime * 100;

   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      position += front * velocity;
   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      position -= front * velocity;
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      position -= right * velocity;
   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      position += right * velocity;
   }

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLFWwindow* window, GLboolean constrainPitch) {
   int screenWidth, screenHeight;
   glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
   // Normalize the mouse movement by dividing by screen width/height (you could use the window size)
   float normalizedX = xoffset / screenWidth;  // screenWidth = width of your window
   float normalizedY = yoffset / screenHeight; // screenHeight = height of your window

   normalizedX *= mouseSensitivity;
   normalizedY *= mouseSensitivity;

   yaw += normalizedX;
   pitch += normalizedY;

   if (constrainPitch) {
      if (pitch > 89.0f)
         pitch = 89.0f;
      if (pitch < -89.0f)
         pitch = -89.0f;
      }

   updateCameraVectors();
   }


void Camera::ProcessMouseScroll(float yoffset) {
   zoom -= (float)yoffset;
   if (zoom < 1.0f)
      zoom = 1.0f;
   if (zoom > 45.0f)
      zoom = 45.0f;
   }

void Camera::updateCameraVectors() {
   glm::vec3 newFront;
   newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
   newFront.y = sin(glm::radians(pitch));
   newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
   front = glm::normalize(newFront);

   right = glm::normalize(glm::cross(front, worldUp));
   up = glm::normalize(glm::cross(right, front));
   }
