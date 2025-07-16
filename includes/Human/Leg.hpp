#pragma once

#include "../humangl.hpp"
#include "BodyPart.hpp"

// Base Leg class
class Leg : public BodyPartRenderer {
protected:
    float positionX, positionY, positionZ;
    float thighX;
    float lowerLegX;

public:
    Leg(float x, float y, float z);
    virtual ~Leg() = default;

    void render() override;
    
    // Leg rotation methods
    void setThighRotation(float x);
    void setLowerLegRotation(float x);
    void getThighRotation(float& x) const;
    void getLowerLegRotation(float& x) const;
};

// Left Leg class
class LeftLeg : public Leg {
public:
    LeftLeg();
    virtual ~LeftLeg() = default;
};

// Right Leg class
class RightLeg : public Leg {
public:
    RightLeg();
    virtual ~RightLeg() = default;
};
