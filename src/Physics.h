#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>

class Physics {
public:
   void Physics::Run(Scene& scene);
   static bool Raycast(const glm::vec3& rayOrigin, const glm::vec3& rayDir, int layer);
   };

#endif PHYSICS_H