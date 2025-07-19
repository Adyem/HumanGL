#pragma once

#include "../humangl.hpp"
#include "BodyPart.hpp"

// Eyes class - rendered as part of head
class Eyes : public BodyPartRenderer {
private:
    float headRotationX;
    float headRotationY;

public:
    Eyes();
    virtual ~Eyes() = default;

    void render(MatrixStack& matrixStack) override;
    
    // Sync with head rotation
    void setHeadRotation(float x, float y);
};
