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
