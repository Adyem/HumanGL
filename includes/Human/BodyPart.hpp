#pragma once

#include "../humangl.hpp"
#include "../Matrix/MatrixStack.hpp"

// Base class for all body part renderers
class BodyPartRenderer {
protected:
    float colorR, colorG, colorB;

public:
    BodyPartRenderer(float r = 1.0f, float g = 1.0f, float b = 1.0f);
    virtual ~BodyPartRenderer() = default;

    // Pure virtual render method
    virtual void render(MatrixStack& matrixStack) = 0;

    // Color management
    void setColor(float r, float g, float b);

protected:
    // Helper method for drawing a colored cube
    void drawColoredCube(float r, float g, float b);
};
