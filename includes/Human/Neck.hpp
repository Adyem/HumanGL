#pragma once

#include "../humangl.hpp"
#include "BodyPart.hpp"

// Neck class
class Neck : public BodyPartRenderer {
public:
    Neck();
    virtual ~Neck() = default;

    void render(MatrixStack& matrixStack) override;
};
