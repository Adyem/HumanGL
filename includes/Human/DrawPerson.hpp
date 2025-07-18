#pragma once

#include "../humangl.hpp"
#include "Head.hpp"
#include "Shoulder.hpp"
#include "Arm.hpp"
#include "Leg.hpp"
#include <map>

class DrawPerson {
private:
    // Body part instances
    std::unique_ptr<Torso> torso;
    std::unique_ptr<Neck> neck;
    std::unique_ptr<Head> head;
    std::unique_ptr<Eyes> eyes;
    std::unique_ptr<LeftShoulder> leftShoulder;
    std::unique_ptr<RightShoulder> rightShoulder;
    std::unique_ptr<LeftArm> leftArm;
    std::unique_ptr<RightArm> rightArm;
    std::unique_ptr<LeftLeg> leftLeg;
    std::unique_ptr<RightLeg> rightLeg;

    // Global transformations
    float torsoRotationY;
    float jumpHeight;

public:
    DrawPerson();
    ~DrawPerson() = default;

    // Main render method
    void render();

    // Global transformation methods
    void setTorsoRotation(float y);
    void setJumpHeight(float height);
    float getTorsoRotation() const;

    // Individual body part control methods
    void setHeadRotation(float x, float y);
    void setLeftArmRotation(float upperX, float upperZ, float forearmX);
    void setRightArmRotation(float upperX, float upperZ, float forearmX);
    void setLeftLegRotation(float thighX, float lowerLegX);
    void setRightLegRotation(float thighX, float lowerLegX);

    // Getters for current rotations
    void getHeadRotation(float& x, float& y) const;
    void getLeftArmRotation(float& upperX, float& upperZ, float& forearmX) const;
    void getRightArmRotation(float& upperX, float& upperZ, float& forearmX) const;
    void getLeftLegRotation(float& thighX, float& lowerLegX) const;
    void getRightLegRotation(float& thighX, float& lowerLegX) const;

    // Body part customization methods
    void setBodyPartColor(BodyPart part, float r, float g, float b);
    void setBodyPartScale(BodyPart part, float scaleX, float scaleY, float scaleZ);
    void applyBodyPartSettings(const std::map<BodyPart, BodyPartSettings>& settings);
};
