#include "ImGuiMenubar.h"

void IGMenubar::RenderMenuBar()
{
    if (ImGui::BeginMainMenuBar()) 
    {
        if (ImGui::BeginMenu("File")) 
        {
            if (ImGui::MenuItem("New")) 
            {
                // Handle new file action
            }
            if (ImGui::MenuItem("Open", "Ctrl+O")) 
            {
                // Handle open file action
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) 
            {
                // Handle save action
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) 
            {
                // Handle exit action
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) 
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) 
            {
                // Handle undo action
            }
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) 
            {
                // Handle redo action
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Copy", "Ctrl+C")) {}
            if (ImGui::MenuItem("Paste", "Ctrl+V")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help")) 
        {
            if (ImGui::MenuItem("About")) 
            {
                // Show "About" window
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
