#include "../../includes/Simulation/AnimationManager.hpp"

AnimationManager::AnimationManager(DrawPerson& person)
    : drawPerson(person), currentAnimation(NONE), animationTime(0.0f), jumpHeight(0.0f), baseTorsoRotation(0.0f) {
}

void AnimationManager::update() {
    if (currentAnimation == NONE) return;

    // Increment animation time
    animationTime += ANIMATION_SPEED;

    // Update the current animation
    switch (currentAnimation) {
        case WALKING:
            updateWalkingAnimation();
            break;
        case JUMPING:
            updateJumpingAnimation();
            break;
        case DANCING:
            updateDancingAnimation();
            break;
        case KUNGFU:
            updateKungFuAnimation();
            break;
        case NONE:
            break;
    }
}

void AnimationManager::startWalking() {
    currentAnimation = WALKING;
    animationTime = 0.0f;
}

void AnimationManager::startJumping() {
    if (currentAnimation == NONE) {
        currentAnimation = JUMPING;
        animationTime = 0.0f;
        jumpHeight = 0.0f;
    }
}

void AnimationManager::startDancing() {
    currentAnimation = DANCING;
    animationTime = 0.0f;
}

void AnimationManager::startKungFu() {
    currentAnimation = KUNGFU;
    animationTime = 0.0f;
}

void AnimationManager::stopAnimation() {
    currentAnimation = NONE;
    resetLimbPositions();
    resetAnimationTime();
}

void AnimationManager::updateWalkingAnimation() {
    // Realistic walking animation with natural front-to-back arm movement
    float legSwing = 30.0f * sinf(animationTime * 2.0f);
    float lowerLegBend = fmaxf(0.0f, -40.0f * sinf(animationTime * 2.0f));

    // Left leg leads, right leg follows
    drawPerson.setLeftLegRotation(legSwing, lowerLegBend);
    drawPerson.setRightLegRotation(-legSwing, fmaxf(0.0f, 40.0f * sinf(animationTime * 2.0f)));

    // Natural front-to-back arm swinging (opposite to legs)
    // Upper arm swings forward and back (X-axis rotation) - more forward range
    float upperArmSwing = -35.0f * sinf(animationTime * 2.0f); // Increased forward swing

    // Lower arm (forearm) moves MORE than upper arm - much more forward movement
    float forearmBend = -45.0f * sinf(animationTime * 2.0f + static_cast<float>(M_PI) * 0.3f); // Negative for forward, offset timing

    // Left arm swings forward when right leg is forward (opposite coordination)
    // Parameters: (upperX=front-to-back, upperZ=side-to-side, forearmX=forearm bend)
    drawPerson.setLeftArmRotation(upperArmSwing, 0.0f, forearmBend);
    drawPerson.setRightArmRotation(-upperArmSwing, 0.0f, forearmBend);

    // Slight torso sway and head bob for realism - ADD to base rotation
    float animationSway = 3.0f * sinf(animationTime * 2.0f);
    drawPerson.setTorsoRotation(baseTorsoRotation + animationSway);
    drawPerson.setHeadRotation(2.0f * sinf(animationTime * 2.0f), 0.0f);
}

void AnimationManager::updateJumpingAnimation() {
    // Completely realistic jump animation with proper knee bending and arm movement
    float jumpProgress = animationTime / JUMP_DURATION;
    if (jumpProgress <= 1.0f) {
        jumpHeight = JUMP_MAX_HEIGHT * sinf(jumpProgress * static_cast<float>(M_PI));
        drawPerson.setJumpHeight(jumpHeight);

        if (jumpProgress < 0.25f) {
            // Phase 1: Preparation - bend knees and tilt arms backward
            float prepFactor = jumpProgress / 0.25f;

            // Bend knees deeply for preparation (positive values for forward knee bend)
            drawPerson.setLeftLegRotation(30.0f * prepFactor, 80.0f * prepFactor);
            drawPerson.setRightLegRotation(30.0f * prepFactor, 80.0f * prepFactor);

            // Tilt arms backward for momentum - upper arm
            float upperArmBack = 45.0f * prepFactor;
            // Forearm moves MORE than upper arm - even more backward
            float forearmBack = 60.0f * prepFactor;
            drawPerson.setLeftArmRotation(upperArmBack, 0.0f, forearmBack);
            drawPerson.setRightArmRotation(upperArmBack, 0.0f, forearmBack);

            // Slight forward lean - ADD to base rotation
            float animationLean = 5.0f * prepFactor;
            drawPerson.setTorsoRotation(baseTorsoRotation + animationLean);

        } else if (jumpProgress < 0.4f) {
            // Phase 2: Takeoff - explosive extension
            float takeoffFactor = (jumpProgress - 0.25f) / 0.15f;

            // Rapidly extend legs (correct direction)
            float legExtension = 30.0f - (40.0f * takeoffFactor);
            float kneeExtension = 80.0f - (100.0f * takeoffFactor);
            drawPerson.setLeftLegRotation(legExtension, kneeExtension);
            drawPerson.setRightLegRotation(legExtension, kneeExtension);

            // Swing arms forward powerfully - upper arm
            float upperArmSwing = 45.0f - (90.0f * takeoffFactor);
            // Forearm moves MORE than upper arm - more forward swing
            float forearmSwing = 60.0f - (120.0f * takeoffFactor);
            drawPerson.setLeftArmRotation(upperArmSwing, 0.0f, forearmSwing);
            drawPerson.setRightArmRotation(upperArmSwing, 0.0f, forearmSwing);

            // Return torso to upright - ADD to base rotation
            float animationLean = 5.0f - (5.0f * takeoffFactor);
            drawPerson.setTorsoRotation(baseTorsoRotation + animationLean);

        } else if (jumpProgress < 0.75f) {
            // Phase 3: Airborne - stretched position
            // Legs fully extended and slightly forward (correct direction)
            drawPerson.setLeftLegRotation(-15.0f, 10.0f);
            drawPerson.setRightLegRotation(-15.0f, 10.0f);

            // Arms forward for balance - upper arm
            float upperArmForward = -30.0f;
            // Forearm moves MORE than upper arm - more forward
            float forearmForward = -45.0f;
            drawPerson.setLeftArmRotation(upperArmForward, 0.0f, forearmForward);
            drawPerson.setRightArmRotation(upperArmForward, 0.0f, forearmForward);

            // Upright torso - preserve base rotation
            drawPerson.setTorsoRotation(baseTorsoRotation);

        } else {
            // Phase 4: Landing preparation - bend knees for impact
            float landFactor = (jumpProgress - 0.75f) / 0.25f;

            // Bend knees for landing (correct direction)
            drawPerson.setLeftLegRotation(-15.0f + (35.0f * landFactor), 10.0f + (50.0f * landFactor));
            drawPerson.setRightLegRotation(-15.0f + (35.0f * landFactor), 10.0f + (50.0f * landFactor));

            // Arms come down for balance - upper arm
            float upperArmDown = -30.0f + (20.0f * landFactor);
            // Forearm moves MORE than upper arm - comes down more
            float forearmDown = -45.0f + (35.0f * landFactor);
            drawPerson.setLeftArmRotation(upperArmDown, 0.0f, forearmDown);
            drawPerson.setRightArmRotation(upperArmDown, 0.0f, forearmDown);

            // Slight forward lean for landing - ADD to base rotation
            float animationLean = 3.0f * landFactor;
            drawPerson.setTorsoRotation(baseTorsoRotation + animationLean);
        }
    } else {
        // Jump finished, reset to standing position
        currentAnimation = NONE;
        jumpHeight = 0.0f;
        drawPerson.setJumpHeight(0.0f);
        resetLimbPositions();
        animationTime = 0.0f;
    }
}

void AnimationManager::updateDancingAnimation() {
    // Macarena dance animation - realistic sequence
    float cycleTime = fmodf(animationTime, 8.0f); // 8-second cycle

    if (cycleTime < 1.0f) {
        // Step 1: Right hand to left shoulder
        drawPerson.setRightArmRotation(-45.0f, -60.0f, 45.0f);
        drawPerson.setLeftArmRotation(0.0f, 0.0f, 0.0f);
    } else if (cycleTime < 2.0f) {
        // Step 2: Left hand to right shoulder
        drawPerson.setRightArmRotation(-45.0f, -60.0f, 45.0f);
        drawPerson.setLeftArmRotation(-45.0f, 60.0f, -45.0f);
    } else if (cycleTime < 3.0f) {
        // Step 3: Right hand to back of head
        drawPerson.setRightArmRotation(-120.0f, -30.0f, 0.0f);
        drawPerson.setLeftArmRotation(-45.0f, 60.0f, -45.0f);
    } else if (cycleTime < 4.0f) {
        // Step 4: Left hand to back of head
        drawPerson.setRightArmRotation(-120.0f, -30.0f, 0.0f);
        drawPerson.setLeftArmRotation(-120.0f, 30.0f, 0.0f);
    } else if (cycleTime < 5.0f) {
        // Step 5: Right hand to right hip
        drawPerson.setRightArmRotation(30.0f, 0.0f, 30.0f);
        drawPerson.setLeftArmRotation(-120.0f, 30.0f, 0.0f);
    } else if (cycleTime < 6.0f) {
        // Step 6: Left hand to left hip
        drawPerson.setRightArmRotation(30.0f, 0.0f, 30.0f);
        drawPerson.setLeftArmRotation(30.0f, 0.0f, -30.0f);
    } else if (cycleTime < 7.0f) {
        // Step 7: Hip sway right
        drawPerson.setRightArmRotation(30.0f, 0.0f, 30.0f);
        drawPerson.setLeftArmRotation(30.0f, 0.0f, -30.0f);
        drawPerson.setTorsoRotation(15.0f);
    } else {
        // Step 8: Hip sway left and jump
        drawPerson.setRightArmRotation(30.0f, 0.0f, 30.0f);
        drawPerson.setLeftArmRotation(30.0f, 0.0f, -30.0f);
        drawPerson.setTorsoRotation(-15.0f);
        // Small hop
        drawPerson.setJumpHeight(0.3f * sinf((cycleTime - 7.0f) * 6.0f * static_cast<float>(M_PI)));
    }

    // Subtle leg movement and head bobbing
    drawPerson.setLeftLegRotation(5.0f * sinf(animationTime * 2.0f), 0.0f);
    drawPerson.setRightLegRotation(5.0f * sinf(animationTime * 2.0f + static_cast<float>(M_PI)), 0.0f);
    drawPerson.setHeadRotation(3.0f * sinf(animationTime * 1.5f), 5.0f * cosf(animationTime * 1.2f));
}

void AnimationManager::updateKungFuAnimation() {
    // Realistic kung fu fighting animation with fluid movements
    float cycleTime = fmodf(animationTime, 4.0f); // 4-second cycle

    if (cycleTime < 0.5f) {
        // Fighting stance - guard position
        drawPerson.setLeftArmRotation(-45.0f, -30.0f, -20.0f);
        drawPerson.setRightArmRotation(-45.0f, 30.0f, 20.0f);
        drawPerson.setLeftLegRotation(-10.0f, 0.0f);
        drawPerson.setRightLegRotation(10.0f, 0.0f);
        drawPerson.setTorsoRotation(-5.0f);
    } else if (cycleTime < 1.0f) {
        // Right punch with body rotation
        float punchProgress = (cycleTime - 0.5f) / 0.5f;
        drawPerson.setLeftArmRotation(-45.0f, -30.0f, -20.0f);
        drawPerson.setRightArmRotation(-10.0f + (-70.0f * punchProgress), 30.0f, 20.0f);
        drawPerson.setLeftLegRotation(-10.0f, 0.0f);
        drawPerson.setRightLegRotation(10.0f, 0.0f);
        drawPerson.setTorsoRotation(-5.0f + (20.0f * punchProgress));
    } else if (cycleTime < 1.5f) {
        // Return to guard and prepare left punch
        drawPerson.setLeftArmRotation(-45.0f, -30.0f, -20.0f);
        drawPerson.setRightArmRotation(-45.0f, 30.0f, 20.0f);
        drawPerson.setLeftLegRotation(-10.0f, 0.0f);
        drawPerson.setRightLegRotation(10.0f, 0.0f);
        drawPerson.setTorsoRotation(5.0f);
    } else if (cycleTime < 2.0f) {
        // Left punch with body rotation
        float punchProgress = (cycleTime - 1.5f) / 0.5f;
        drawPerson.setLeftArmRotation(-10.0f + (-70.0f * punchProgress), -30.0f, -20.0f);
        drawPerson.setRightArmRotation(-45.0f, 30.0f, 20.0f);
        drawPerson.setLeftLegRotation(-10.0f, 0.0f);
        drawPerson.setRightLegRotation(10.0f, 0.0f);
        drawPerson.setTorsoRotation(5.0f + (-20.0f * punchProgress));
    } else if (cycleTime < 2.5f) {
        // Prepare for high kick
        drawPerson.setLeftArmRotation(-30.0f, -45.0f, -30.0f);
        drawPerson.setRightArmRotation(-30.0f, 45.0f, 30.0f);
        drawPerson.setLeftLegRotation(-20.0f, -10.0f);
        drawPerson.setRightLegRotation(-20.0f, -10.0f);
        drawPerson.setTorsoRotation(0.0f);
    } else if (cycleTime < 3.0f) {
        // High kick execution
        float kickProgress = (cycleTime - 2.5f) / 0.5f;
        drawPerson.setLeftArmRotation(-30.0f, -45.0f, -30.0f);
        drawPerson.setRightArmRotation(-30.0f, 45.0f, 30.0f);
        drawPerson.setLeftLegRotation(-20.0f, -10.0f);
        drawPerson.setRightLegRotation(-20.0f + (110.0f * kickProgress), -10.0f + (20.0f * kickProgress));
        drawPerson.setTorsoRotation(-10.0f * kickProgress);
    } else if (cycleTime < 3.5f) {
        // Block position
        drawPerson.setLeftArmRotation(-90.0f, -20.0f, -45.0f);
        drawPerson.setRightArmRotation(-90.0f, 20.0f, 45.0f);
        drawPerson.setLeftLegRotation(-15.0f, 0.0f);
        drawPerson.setRightLegRotation(-15.0f, 0.0f);
        drawPerson.setTorsoRotation(0.0f);
    } else {
        // Return to fighting stance
        drawPerson.setLeftArmRotation(-45.0f, -30.0f, -20.0f);
        drawPerson.setRightArmRotation(-45.0f, 30.0f, 20.0f);
        drawPerson.setLeftLegRotation(-10.0f, 0.0f);
        drawPerson.setRightLegRotation(10.0f, 0.0f);
        drawPerson.setTorsoRotation(-5.0f);
    }

    // Add subtle head movement for focus
    drawPerson.setHeadRotation(2.0f * sinf(animationTime * 1.5f), 3.0f * cosf(animationTime * 1.2f));
}

void AnimationManager::resetLimbPositions() {
    drawPerson.setLeftLegRotation(0.0f, 0.0f);
    drawPerson.setRightLegRotation(0.0f, 0.0f);
    drawPerson.setLeftArmRotation(0.0f, 0.0f, 0.0f);
    drawPerson.setRightArmRotation(0.0f, 0.0f, 0.0f);
    drawPerson.setHeadRotation(0.0f, 0.0f);
    drawPerson.setJumpHeight(0.0f);
}

void AnimationManager::resetAnimationTime() {
    animationTime = 0.0f;
    jumpHeight = 0.0f;
}

void AnimationManager::resetToDefaultPosition() {
    // Stop any current animation
    currentAnimation = NONE;

    // Reset all limb positions to default
    resetLimbPositions();
    resetAnimationTime();

    // Reset torso rotation to face forward
    baseTorsoRotation = 0.0f;
    drawPerson.setTorsoRotation(0.0f);
}

void AnimationManager::updateBaseTorsoRotation() {
    // Update base torso rotation from current DrawPerson state
    // This preserves user input during animations
    baseTorsoRotation = drawPerson.getTorsoRotation();
}
