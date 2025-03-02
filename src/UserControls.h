
#ifndef USERCONTROLS_H
#define USERCONTROLS_H

#include "GLFW/glfw3.h"
#include "imgui.h"
#include <imgui_internal.h>
#include <string>

#define CONTROL_STATE_WINDOW 0
#define CONTROL_STATE_VIEWPORT 1


class UserControls {
private:
   UserControls();
public:
   static int controlState;
   static UserControls* instance;
   static UserControls* getInstance();

   void setControlState(int newState);
   bool isMouseInsideImGuiWindow(std::string windowName);
   void update(GLFWwindow* window);
};

#endif