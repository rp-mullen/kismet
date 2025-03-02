#pragma once
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Component.h"

class GameObject {
private:
   std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

public:
   template <typename T, typename... Args>
   T* addComponent(Args&&... args) {
      std::type_index typeIndex(typeid(T));
      auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
      T* ptr = component.get();
      components[typeIndex] = std::move(component);
      return ptr;
      }

   template <typename T>
   T* getComponent() {
      std::type_index typeIndex(typeid(T));
      auto it = components.find(typeIndex);
      return (it != components.end()) ? static_cast<T*>(it->second.get()) : nullptr;
      }

   void update(float deltaTime) {
      for (auto& componentPair : components) {
         componentPair.second->update(deltaTime);
         }
      }

   void render() {
      for (auto& componentPair : components) {
         componentPair.second->render();
         }
      }
   };
