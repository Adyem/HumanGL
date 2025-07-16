#pragma once

#include "../humangl.hpp"

class MouseHandler {
private:
    int mouseX;
    int mouseY;
    bool mousePressed;
    bool mouseReleased;

public:
    MouseHandler();
    ~MouseHandler();
    
    // Update mouse position
    void updateMousePosition(int x, int y);
    
    // Update mouse button states
    void setMousePressed(bool pressed);
    void setMouseReleased(bool released);
    
    // Get current mouse state
    int getMouseX() const { return mouseX; }
    int getMouseY() const { return mouseY; }
    bool isMousePressed() const { return mousePressed; }
    bool isMouseReleased() const { return mouseReleased; }
    
    // Update button hover states based on mouse position
    void updateButtonHover(std::vector<MenuButton>& buttons);
    
    // Check if any button was clicked and return its index (-1 if none)
    int checkButtonClick(const std::vector<MenuButton>& buttons);
    
    // Reset mouse state (call after processing events)
    void resetMouseState();
};
