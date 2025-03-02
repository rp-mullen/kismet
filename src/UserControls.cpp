#include "UserControls.h"
#include <iostream>
void UserControls::setControlState(int newState) {
   controlState = newState;
   }

UserControls* UserControls::instance = nullptr;
int UserControls::controlState = CONTROL_STATE_WINDOW;

UserControls::UserControls() {}

UserControls* UserControls::getInstance() {

   if (instance == nullptr) {
      instance = new UserControls();
      return instance;
      }
   else {
      return instance;
      }
   }

bool UserControls::isMouseInsideImGuiWindow(std::string windowName) {
   // Get the current ImGui window
   ImGuiWindow* window = ImGui::FindWindowByName(windowName.c_str());

   if (window == nullptr) {
      
      return false;
      }
   // Get the mouse position
   ImVec2 mousePos = ImGui::GetIO().MousePos;

   // Check if the mouse is inside the window
   bool inside = (mousePos.x >= window->Pos.x && mousePos.x <= window->Pos.x + window->Size.x) &&
      (mousePos.y >= window->Pos.y && mousePos.y <= window->Pos.y + window->Size.y);

   return inside;
   }


void UserControls::update(GLFWwindow* window) {
   if (isMouseInsideImGuiWindow("Viewport")) {
      setControlState(CONTROL_STATE_VIEWPORT);
      }
   else {
      setControlState(CONTROL_STATE_WINDOW);
      }
   }