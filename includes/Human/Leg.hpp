#pragma once

#include "../humangl.hpp"
#include "BodyPart.hpp"

// Base Leg class
class Leg : public BodyPartRenderer {
protected:
    float positionX, positionY, positionZ;
    float thighX;
    float lowerLegX;

    // Individual part colors
    float thighR, thighG, thighB;
    float lowerLegR, lowerLegG, lowerLegB;

public:
    Leg(float x, float y, float z);
    virtual ~Leg() = default;

    void render() override;
    
    // Leg rotation methods
    void setThighRotation(float x);
    void setLowerLegRotation(float x);
    void getThighRotation(float& x) const;
    void getLowerLegRotation(float& x) const;

    // Individual part color methods
    void setThighColor(float r, float g, float b);
    void setLowerLegColor(float r, float g, float b);
};


