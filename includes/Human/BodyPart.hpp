#pragma once

#include "../humangl.hpp"
#include "../Matrix/MatrixStack.hpp"

// Base class for all body part renderers
class BodyPartRenderer {
protected:
    float colorR, colorG, colorB;
    float scaleX, scaleY, scaleZ;

public:
    BodyPartRenderer(float r = 1.0f, float g = 1.0f, float b = 1.0f);
    virtual ~BodyPartRenderer() = default;

    // Pure virtual render method (PDF compliant - uses custom MatrixStack)
    virtual void render(MatrixStack& matrixStack) = 0;

    // Color management
    void setColor(float r, float g, float b);

    // Scale management
    void setScale(float scaleX, float scaleY, float scaleZ);

protected:
    // PDF compliant method - draws cube with custom matrix transformations (100% compliant)
    void drawColoredCubeWithMatrix(float r, float g, float b, const MatrixStack& matrixStack);
};
