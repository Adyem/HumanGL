#include "../../includes/Menus/MenuRenderer.hpp"

MenuRenderer::MenuRenderer(TextRenderer& textRend)
    : textRenderer(textRend), windowWidth(HUMANGL_DEFAULT_WINDOW_WIDTH), windowHeight(HUMANGL_DEFAULT_WINDOW_HEIGHT) {
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
    glOrtho(HUMANGL_OPENGL_AXIS_NONE, windowWidth, windowHeight, HUMANGL_OPENGL_AXIS_NONE, -HUMANGL_OPENGL_AXIS_Y, HUMANGL_OPENGL_AXIS_Y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
}

void MenuRenderer::setup3D() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    float fov = HUMANGL_DEFAULT_FOV;
    float nearPlane = HUMANGL_NEAR_PLANE;
    float farPlane = HUMANGL_FAR_PLANE;

    float top = nearPlane * tanf(DEGREES_TO_RADIANS(fov) / 2.0f);
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
        drawRect(button.x, button.y, button.width, button.height,
                 HUMANGL_MENU_BUTTON_HOVER_R, HUMANGL_MENU_BUTTON_HOVER_G,
                 HUMANGL_MENU_BUTTON_HOVER_B, HUMANGL_MENU_BUTTON_HOVER_A);
    } else {
        drawRect(button.x, button.y, button.width, button.height,
                 HUMANGL_MENU_BUTTON_NORMAL_R, HUMANGL_MENU_BUTTON_NORMAL_G,
                 HUMANGL_MENU_BUTTON_NORMAL_B, HUMANGL_MENU_BUTTON_NORMAL_A);
    }
    
    // Button border
    glColor3f(HUMANGL_MENU_BUTTON_BORDER_R, HUMANGL_MENU_BUTTON_BORDER_G, HUMANGL_MENU_BUTTON_BORDER_B);
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
    textRenderer.drawText(textX, textY, button.text, HUMANGL_MENU_TEXT_R, HUMANGL_MENU_TEXT_G, HUMANGL_MENU_TEXT_B);
}

void MenuRenderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}


