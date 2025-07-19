#include "../../includes/Human/DrawPerson.hpp"

DrawPerson::DrawPerson() : torsoRotationY(HUMANGL_OPENGL_AXIS_NONE), jumpHeight(HUMANGL_OPENGL_AXIS_NONE) {
    // Initialize all body parts
    torso = std::make_unique<Torso>();
    neck = std::make_unique<Neck>();
    head = std::make_unique<Head>();
    eyes = std::make_unique<Eyes>();
    leftShoulder = std::make_unique<LeftShoulder>();
    rightShoulder = std::make_unique<RightShoulder>();
    leftArm = std::make_unique<LeftArm>();
    rightArm = std::make_unique<RightArm>();
    leftLeg = std::make_unique<LeftLeg>();
    rightLeg = std::make_unique<RightLeg>();
}

void DrawPerson::render(MatrixStack& matrixStack) {
    // Enable face culling for better performance
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // 100% PDF compliant - ONLY use custom MatrixStack, NO OpenGL matrix functions!

    // Apply global transformations using ONLY custom matrix stack
    matrixStack.pushMatrix();
    matrixStack.translate(HUMANGL_OPENGL_AXIS_NONE, jumpHeight, HUMANGL_OPENGL_AXIS_NONE);
    matrixStack.rotateY(torsoRotationY);

    // Draw body parts in hierarchical order
    torso->render(matrixStack);           // Base of hierarchy
    neck->render(matrixStack);            // Connected to torso
    head->render(matrixStack);            // Connected to neck
    eyes->render(matrixStack);            // Eyes on the head (shows front direction)

    // Draw shoulder joints
    leftShoulder->render(matrixStack);    // Left shoulder joint
    rightShoulder->render(matrixStack);   // Right shoulder joint

    // Draw arms (connected to shoulders)
    leftArm->render(matrixStack);         // Left arm (upper arm + forearm connected)
    rightArm->render(matrixStack);        // Right arm (upper arm + forearm connected)

    // Draw legs (connected to torso)
    leftLeg->render(matrixStack);         // Left leg (thigh + lower leg connected)
    rightLeg->render(matrixStack);        // Right leg (thigh + lower leg connected)

    // Pop from custom matrix stack only - NO OpenGL matrix calls!
    matrixStack.popMatrix();

    // Disable states we enabled
    glDisable(GL_CULL_FACE);
}

void DrawPerson::setTorsoRotation(float y) {
    torsoRotationY = y;
}

void DrawPerson::setJumpHeight(float height) {
    jumpHeight = height;
}

float DrawPerson::getTorsoRotation() const {
    return torsoRotationY;
}

void DrawPerson::setHeadRotation(float x, float y) {
    head->setHeadRotation(x, y);
    eyes->setHeadRotation(x, y);
}

void DrawPerson::setLeftArmRotation(float upperX, float upperZ, float forearmX) {
    leftArm->setUpperArmRotation(upperX, upperZ);
    leftArm->setForearmRotation(forearmX);
}

void DrawPerson::setRightArmRotation(float upperX, float upperZ, float forearmX) {
    rightArm->setUpperArmRotation(upperX, upperZ);
    rightArm->setForearmRotation(forearmX);
}

void DrawPerson::setLeftLegRotation(float thighX, float lowerLegX) {
    leftLeg->setThighRotation(thighX);
    leftLeg->setLowerLegRotation(lowerLegX);
}

void DrawPerson::setRightLegRotation(float thighX, float lowerLegX) {
    rightLeg->setThighRotation(thighX);
    rightLeg->setLowerLegRotation(lowerLegX);
}

void DrawPerson::getHeadRotation(float& x, float& y) const {
    head->getHeadRotation(x, y);
}

void DrawPerson::getLeftArmRotation(float& upperX, float& upperZ, float& forearmX) const {
    leftArm->getUpperArmRotation(upperX, upperZ);
    leftArm->getForearmRotation(forearmX);
}

void DrawPerson::getRightArmRotation(float& upperX, float& upperZ, float& forearmX) const {
    rightArm->getUpperArmRotation(upperX, upperZ);
    rightArm->getForearmRotation(forearmX);
}

void DrawPerson::getLeftLegRotation(float& thighX, float& lowerLegX) const {
    leftLeg->getThighRotation(thighX);
    leftLeg->getLowerLegRotation(lowerLegX);
}

void DrawPerson::getRightLegRotation(float& thighX, float& lowerLegX) const {
    rightLeg->getThighRotation(thighX);
    rightLeg->getLowerLegRotation(lowerLegX);
}

void DrawPerson::setBodyPartColor(BodyPart part, float r, float g, float b) {
    switch (part) {
        case BODY_PART_HEAD:
            head->setColor(r, g, b);
            break;
        case BODY_PART_TORSO:
            torso->setColor(r, g, b);
            break;
        case BODY_PART_NECK:
            neck->setColor(r, g, b);
            break;
        case BODY_PART_EYES:
            eyes->setColor(r, g, b);
            break;
        case BODY_PART_LEFT_SHOULDER:
            leftShoulder->setColor(r, g, b);
            break;
        case BODY_PART_RIGHT_SHOULDER:
            rightShoulder->setColor(r, g, b);
            break;
        // Individual arm parts
        case BODY_PART_LEFT_UPPER_ARM:
            leftArm->setUpperArmColor(r, g, b);
            break;
        case BODY_PART_RIGHT_UPPER_ARM:
            rightArm->setUpperArmColor(r, g, b);
            break;
        case BODY_PART_LEFT_FOREARM:
            leftArm->setForearmColor(r, g, b);
            break;
        case BODY_PART_RIGHT_FOREARM:
            rightArm->setForearmColor(r, g, b);
            break;
        // Individual leg parts
        case BODY_PART_LEFT_THIGH:
            leftLeg->setThighColor(r, g, b);
            break;
        case BODY_PART_RIGHT_THIGH:
            rightLeg->setThighColor(r, g, b);
            break;
        case BODY_PART_LEFT_LOWER_LEG:
            leftLeg->setLowerLegColor(r, g, b);
            break;
        case BODY_PART_RIGHT_LOWER_LEG:
            rightLeg->setLowerLegColor(r, g, b);
            break;
        // General arm/leg (apply to both upper and lower parts)
        case BODY_PART_LEFT_ARM:
            leftArm->setUpperArmColor(r, g, b);
            leftArm->setForearmColor(r, g, b);
            break;
        case BODY_PART_RIGHT_ARM:
            rightArm->setUpperArmColor(r, g, b);
            rightArm->setForearmColor(r, g, b);
            break;
        case BODY_PART_LEFT_LEG:
            leftLeg->setThighColor(r, g, b);
            leftLeg->setLowerLegColor(r, g, b);
            break;
        case BODY_PART_RIGHT_LEG:
            rightLeg->setThighColor(r, g, b);
            rightLeg->setLowerLegColor(r, g, b);
            break;
        default:
            break;
    }
}

void DrawPerson::setBodyPartScale(BodyPart part, float scaleX, float scaleY, float scaleZ) {
    switch (part) {
        case BODY_PART_HEAD:
            head->setScale(scaleX, scaleY, scaleZ);
            break;
        case BODY_PART_TORSO:
            torso->setScale(scaleX, scaleY, scaleZ);
            break;
        case BODY_PART_NECK:
            neck->setScale(scaleX, scaleY, scaleZ);
            break;
        case BODY_PART_EYES:
            eyes->setScale(scaleX, scaleY, scaleZ);
            break;
        case BODY_PART_LEFT_SHOULDER:
            leftShoulder->setScale(scaleX, scaleY, scaleZ);
            break;
        case BODY_PART_RIGHT_SHOULDER:
            rightShoulder->setScale(scaleX, scaleY, scaleZ);
            break;
        // Individual arm parts
        case BODY_PART_LEFT_UPPER_ARM:
            leftArm->setScale(scaleX, scaleY, scaleZ);  // Note: This affects both upper arm and forearm
            break;
        case BODY_PART_RIGHT_UPPER_ARM:
            rightArm->setScale(scaleX, scaleY, scaleZ);  // Note: This affects both upper arm and forearm
            break;
        case BODY_PART_LEFT_FOREARM:
            leftArm->setScale(scaleX, scaleY, scaleZ);  // Note: This affects both upper arm and forearm
            break;
        case BODY_PART_RIGHT_FOREARM:
            rightArm->setScale(scaleX, scaleY, scaleZ);  // Note: This affects both upper arm and forearm
            break;
        // Individual leg parts
        case BODY_PART_LEFT_THIGH:
            leftLeg->setScale(scaleX, scaleY, scaleZ);  // Note: This affects both thigh and lower leg
            break;
        case BODY_PART_RIGHT_THIGH:
            rightLeg->setScale(scaleX, scaleY, scaleZ);  // Note: This affects both thigh and lower leg
            break;
        case BODY_PART_LEFT_LOWER_LEG:
            leftLeg->setScale(scaleX, scaleY, scaleZ);  // Note: This affects both thigh and lower leg
            break;
        case BODY_PART_RIGHT_LOWER_LEG:
            rightLeg->setScale(scaleX, scaleY, scaleZ);  // Note: This affects both thigh and lower leg
            break;
        // General arm/leg (apply to both upper and lower parts)
        case BODY_PART_LEFT_ARM:
            leftArm->setScale(scaleX, scaleY, scaleZ);
            break;
        case BODY_PART_RIGHT_ARM:
            rightArm->setScale(scaleX, scaleY, scaleZ);
            break;
        case BODY_PART_LEFT_LEG:
            leftLeg->setScale(scaleX, scaleY, scaleZ);
            break;
        case BODY_PART_RIGHT_LEG:
            rightLeg->setScale(scaleX, scaleY, scaleZ);
            break;
        default:
            break;
    }
}

void DrawPerson::applyBodyPartSettings(const std::map<BodyPart, BodyPartSettings>& settings) {
    for (const auto& pair : settings) {
        BodyPart part = pair.first;
        const BodyPartSettings& setting = pair.second;

        // Apply color
        setBodyPartColor(part, setting.color.r, setting.color.g, setting.color.b);

        // Apply scale
        setBodyPartScale(part, setting.scale.x, setting.scale.y, setting.scale.z);

        // TODO: Apply rotation and position when needed
    }
}
