
#include "Model.h"
#include "TransformComponent.cpp"



void Model::Draw(Shader& shader) {
  
   shader.use();
   for (Mesh& mesh : meshes)
      mesh.Draw();
      }


void Model::loadModel(const char* path) {
   this->path = path;
   Assimp::Importer importer;
   const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

   if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
      return;
      }

   processNode(scene->mRootNode, scene);
   }

void Model::processNode(aiNode* node, const aiScene* scene) {
   for (unsigned int i = 0; i < node->mNumMeshes; i++) {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      meshes.push_back(processMesh(mesh, scene));
      }

   for (unsigned int i = 0; i < node->mNumChildren; i++) {
      processNode(node->mChildren[i], scene);
      }
   }

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
   std::vector<Vertex> vertices;
   std::vector<unsigned int> indices;

   for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
      Vertex vertex;
      vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
      if (mesh->HasNormals()) {
         vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
         }
      if (mesh->mTextureCoords[0]) {
         vertex.UV = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
         }
      else {
         vertex.UV = glm::vec2(0.0f, 0.0f);
         }
      vertices.push_back(vertex);
      }

   for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];
      for (unsigned int j = 0; j < face.mNumIndices; j++) {
         indices.push_back(face.mIndices[j]);
         }
      }

   return Mesh(vertices, indices);
   }

glm::mat4 Model::getModelMatrix() {  
  glm::mat4 modelMatrix = glm::mat4(1.0f); // Start with identity matrix  

  // Apply transformations  
  const auto& transformComponent = getOwner()->getOwner()->getComponent<TransformComponent>();
  modelMatrix = glm::translate(modelMatrix, transformComponent->position); // Translation
  modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation  
  modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f)); // Scaling  
  return modelMatrix;  
}

bool Model::operator==(const Model& other) const {
   // Example: Compare the file paths of models to determine equality
   return this->path == other.path;
   }
