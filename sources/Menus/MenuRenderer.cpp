#include "../../includes/Menus/MenuRenderer.hpp"

MenuRenderer::MenuRenderer(TextRenderer& textRend) 
    : textRenderer(textRend), windowWidth(800), windowHeight(600) {
}

MenuRenderer::~MenuRenderer() {
}

void MenuRenderer::updateWindowSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}

void MenuRenderer::setup2D() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
}

void MenuRenderer::setup3D() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    
    float top = nearPlane * tanf(fov * M_PI / 360.0f);
    float bottom = -top;
    float right = top * aspectRatio;
    float left = -right;
    
    glFrustum(left, right, bottom, top, nearPlane, farPlane);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void MenuRenderer::drawRect(float x, float y, float width, float height, float r, float g, float b, float a) {
    glColor4f(r, g, b, a);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void MenuRenderer::drawButton(const MenuButton& button) {
    // Button background
    if (button.hovered) {
        drawRect(button.x, button.y, button.width, button.height, 0.3f, 0.5f, 0.8f, 0.8f);
    } else {
        drawRect(button.x, button.y, button.width, button.height, 0.2f, 0.3f, 0.5f, 0.8f);
    }
    
    // Button border
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(button.x, button.y);
    glVertex2f(button.x + button.width, button.y);
    glVertex2f(button.x + button.width, button.y + button.height);
    glVertex2f(button.x, button.y + button.height);
    glEnd();
    
    // Button text (centered)
    int textWidth, textHeight;
    textRenderer.getTextSize(button.text, &textWidth, &textHeight);
    float textX = button.x + (button.width - static_cast<float>(textWidth)) / 2.0f;
    float textY = button.y + (button.height - static_cast<float>(textHeight)) / 2.0f;
    textRenderer.drawText(textX, textY, button.text, 1.0f, 1.0f, 1.0f);
}

void MenuRenderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}


