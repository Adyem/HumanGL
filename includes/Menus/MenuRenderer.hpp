#pragma once

#include "../humangl.hpp"
#include "TextRenderer.hpp"

class MenuRenderer {
protected:
    TextRenderer& textRenderer;
    int windowWidth;
    int windowHeight;

public:
    MenuRenderer(TextRenderer& textRend);
    virtual ~MenuRenderer();

    // Update window dimensions
    void updateWindowSize(int width, int height);

    // Setup 2D orthographic projection for menu rendering
    void setup2D();

    // Setup 3D perspective projection for simulation
    void setup3D();

    // Draw a filled rectangle
    void drawRect(float x, float y, float width, float height, float r, float g, float b, float a = 1.0f);

    // Draw a menu button
    void drawButton(const MenuButton& button);

    // Virtual render method for inheritance
    virtual void render(const std::vector<MenuButton>& buttons) = 0;
	
    // Clear screen with background color
    void clearScreen();
};
