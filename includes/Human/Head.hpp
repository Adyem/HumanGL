#pragma once

#include "../humangl.hpp"
#include "BodyPart.hpp"

// Torso class
class Torso : public BodyPartRenderer {
public:
    Torso();
    virtual ~Torso() = default;

    void render() override;
};

// Neck class
class Neck : public BodyPartRenderer {
public:
    Neck();
    virtual ~Neck() = default;

    void render() override;
};

// Head class
class Head : public BodyPartRenderer {
private:
    float headRotationX;
    float headRotationY;

public:
    Head();
    virtual ~Head() = default;

    void render() override;
    
    // Head-specific rotation methods
    void setHeadRotation(float x, float y);
    void getHeadRotation(float& x, float& y) const;
};

// Eyes class - rendered as part of head
class Eyes : public BodyPartRenderer {
private:
    float headRotationX;
    float headRotationY;

public:
    Eyes();
    virtual ~Eyes() = default;

    void render() override;
    
    // Sync with head rotation
    void setHeadRotation(float x, float y);
};
