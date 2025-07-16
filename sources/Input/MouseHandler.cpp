#include "../../includes/Input/MouseHandler.hpp"

MouseHandler::MouseHandler() 
    : mouseX(0), mouseY(0), mousePressed(false), mouseReleased(false) {
}

MouseHandler::~MouseHandler() {
}

void MouseHandler::updateMousePosition(int x, int y) {
    mouseX = x;
    mouseY = y;
}

void MouseHandler::setMousePressed(bool pressed) {
    mousePressed = pressed;
}

void MouseHandler::setMouseReleased(bool released) {
    mouseReleased = released;
}

void MouseHandler::updateButtonHover(std::vector<MenuButton>& buttons) {
    for (auto& button : buttons) {
        button.hovered = button.isPointInside(static_cast<float>(mouseX), static_cast<float>(mouseY));
    }
}

int MouseHandler::checkButtonClick(const std::vector<MenuButton>& buttons) {
    if (!mouseReleased) {
        return -1; // No click occurred
    }
    
    for (size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i].hovered) {
            return static_cast<int>(i);
        }
    }
    
    return -1; // No button was clicked
}

void MouseHandler::resetMouseState() {
    mousePressed = false;
    mouseReleased = false;
}
