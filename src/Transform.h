
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform {
   glm::vec3 position; // Position of the object
   glm::vec3 rotation; // Rotation in Euler angles (pitch, yaw, roll)
   glm::vec3 scale;    // Scale of the object

   // Constructor with default values (identity transform)
   Transform(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f))
      : position(pos), rotation(rot), scale(scl) {
      }

   // Get Model Matrix based on the position, rotation, and scale
   glm::mat4 GetModelMatrix() const {
      glm::mat4 model = glm::mat4(1.0f); // Identity matrix

      // Apply scale
      model = glm::scale(model, scale);

      // Apply rotation (order: pitch -> yaw -> roll)
      model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
      model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
      model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll

      // Apply translation (position)
      model = glm::translate(model, position);

      return model;
      }
   };

#endif