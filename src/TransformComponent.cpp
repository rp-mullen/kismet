#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class TransformComponent : public Component {
public:
   glm::vec3 position, rotation, scale;

   explicit TransformComponent(GameObject* owner)
      : Component(owner), position(0.0f), rotation(0.0f), scale(1.0f) {
      }

   void update(float deltaTime) override {
      // Example: Update position with velocity (if needed)
      }
   };
