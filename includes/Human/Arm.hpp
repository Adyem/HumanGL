#pragma once

#include "../humangl.hpp"
#include "BodyPart.hpp"

// Base Arm class
class Arm : public BodyPartRenderer {
protected:
    float positionX, positionY, positionZ;
    float upperArmX, upperArmZ;
    float forearmX;

public:
    Arm(float x, float y, float z);
    virtual ~Arm() = default;

    void render() override;
    
    // Arm rotation methods
    void setUpperArmRotation(float x, float z);
    void setForearmRotation(float x);
    void getUpperArmRotation(float& x, float& z) const;
    void getForearmRotation(float& x) const;
};

// Left Arm class
class LeftArm : public Arm {
public:
    LeftArm();
    virtual ~LeftArm() = default;
};

// Right Arm class
class RightArm : public Arm {
public:
    RightArm();
    virtual ~RightArm() = default;
};
