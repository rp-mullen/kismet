
#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Shader.h"
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Transform.h"
#include <iostream>
#include "Component.h"

#include "GameObject.h"

class ModelComponent;

class Model {
public:
   std::vector<Mesh> meshes;
   ModelComponent* owner;
   const char* path;

   explicit Model(ModelComponent* owner) : owner(owner), path("") {}
   explicit Model(ModelComponent* owner,std::vector<Mesh> meshes) : owner(owner), meshes(meshes), path("") {}
   explicit Model(ModelComponent* owner, const char* path) : owner(owner), path(path) {
      loadModel(path);
      std::cout << "Model Loaded: " << path << std::endl;
      std::cout << "Total Meshes: " << meshes.size() << std::endl;


      for (size_t i = 0; i < meshes.size(); ++i) {
         std::cout << "Mesh " << i << " has " << meshes[i].vertices.size() << " vertices" << std::endl;
         }

      }

   bool operator==(const Model& other) const; // Define equality operator

   void Draw(Shader& shader);
   glm::mat4 getModelMatrix();
   Transform getTransform();
   ModelComponent* getOwner() { return owner; }

private:
   void loadModel(const char* path);
   void processNode(aiNode* node, const aiScene* scene);
   Mesh processMesh(aiMesh* mesh, const aiScene* scene);

   

   };

#endif