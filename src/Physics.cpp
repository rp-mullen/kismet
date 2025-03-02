#include "Physics.h"

void Physics::Run(Scene& scene) {
   // Implement physics logic here
   // For example, update positions of objects based on velocity, apply gravity, etc.
   for (Model& model : scene.models) {

      // Update model position based on some physics logic
      // This is just a placeholder; actual physics calculations would go here
      model.position += glm::vec3(0.0f, -0.01f, 0.0f); // Apply gravity
      }
   }