#pragma once

#include "../humangl.hpp"
#include "BodyPart.hpp"

// Base Arm class
class Arm : public BodyPartRenderer {
protected:
    float positionX, positionY, positionZ;
    float upperArmX, upperArmZ;
    float forearmX;

    // Individual part colors
    float upperArmR, upperArmG, upperArmB;
    float forearmR, forearmG, forearmB;

public:
    Arm(float x, float y, float z);
    virtual ~Arm() = default;

    void render(MatrixStack& matrixStack) override;
    
    // Arm rotation methods
    void setUpperArmRotation(float x, float z);
    void setForearmRotation(float x);
    void getUpperArmRotation(float& x, float& z) const;
    void getForearmRotation(float& x) const;

    // Individual part color methods
    void setUpperArmColor(float r, float g, float b);
    void setForearmColor(float r, float g, float b);
};


