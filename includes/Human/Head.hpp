#pragma once

#include "../humangl.hpp"
#include "BodyPart.hpp"

// Head class
class Head : public BodyPartRenderer {
private:
    float headRotationX;
    float headRotationY;

public:
    Head();
    virtual ~Head() = default;

    void render(MatrixStack& matrixStack) override;

    // Head-specific rotation methods
    void setHeadRotation(float x, float y);
    void getHeadRotation(float& x, float& y) const;
};
