#pragma once
#include <string>
#include <memory>

class GameObject; // Forward declaration

class Component {
protected:
   GameObject* owner; // Pointer to the GameObject that owns this component
public:
   explicit Component(GameObject* owner) : owner(owner) {}
   virtual ~Component() = default;

   virtual void update(float deltaTime) {}  // Called every frame
   virtual void render() {}                 // Called for rendering if needed

   GameObject* getOwner() const { return owner; }
   };
