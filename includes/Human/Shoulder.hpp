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

// Left Shoulder class
class LeftShoulder : public Shoulder {
public:
    LeftShoulder();
    virtual ~LeftShoulder() = default;
};

// Right Shoulder class
class RightShoulder : public Shoulder {
public:
    RightShoulder();
    virtual ~RightShoulder() = default;
};
