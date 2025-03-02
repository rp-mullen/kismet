#ifndef RENDERER_H
#define RENDERER_H

// Renderer.h
#include <vector>
#include "Model.h"
#include "ShaderManager.h"



class Renderer {
public:

   Shader* currentShader;
   ShaderManager shaderManager;
   std::vector<Model> models; // Collection of models to be rendered

   Renderer();
   void addModel(const Model& model);
   void removeModel(const Model& model);
   void render() ;

private:
   void uploadUniforms() ;
   };

#endif