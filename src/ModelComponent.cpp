#pragma once
#include "Component.h"
#include "Model.h"

class ModelComponent : public Component {
public:
   Model model;

   explicit ModelComponent(GameObject* owner, const std::string& modelPath)
      : Component(owner), model(this,modelPath.c_str()) {
      }

   explicit ModelComponent(GameObject* owner,Model& inModel)
      : Component(owner), model(inModel){

      }


   void render() override {
      //model.Draw();
      }
   };
