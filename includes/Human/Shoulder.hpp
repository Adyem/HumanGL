#pragma once

#include "../humangl.hpp"
#include "BodyPart.hpp"

// Base Shoulder class
class Shoulder : public BodyPartRenderer {
protected:
    float positionX, positionY, positionZ;

public:
    Shoulder(float x, float y, float z);
    virtual ~Shoulder() = default;

    void render() override;
};


