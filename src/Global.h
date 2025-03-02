#ifndef GLOBAL_H  
#define GLOBAL_H  

#include "Scene.h"  
#include <vector>  
#include "GameObject.h"  

class Global {  
public:  
  Scene scene;  
  GLFWwindow* window;  

  static Global* getInstance() {  
     if (instance == nullptr) {  
        instance = new Global();  
     }  
     return instance;  
  }  

  void setScene(const Scene& newScene) {  
     scene = newScene;  
  }  

  template <typename T>  
  std::vector<GameObject> findObjectsByComponent() {  
     std::vector<GameObject> objects;  
     for (auto& go : scene.gameObjects) {
        if (go.getComponent<T>()) {
           objects.push_back(go);
           }
        }
     return objects;  
  }  

private:  
  Global() {}  // Private constructor  
  Global(const Global&) = delete;  // Prevent copying  
  Global& operator=(const Global&) = delete;  // Prevent assignment  
  static Global* instance;  // Static pointer to hold the instance  
};  

#endif