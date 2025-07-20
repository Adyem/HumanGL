#pragma once

#include "../humangl.hpp"

// Simple interface for menu input (functionality moved to EventHandler)
class MenuInputInterface {
public:
    virtual ~MenuInputInterface() = default;
    virtual bool isEscapePressed() const = 0;
    virtual bool isMKeyPressed() const = 0;
    virtual void resetKeyStates() = 0;
    virtual void handleKeyEvent(const SDL_Event& event) = 0;
    virtual void update() = 0;
};
