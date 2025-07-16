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
    float legSwing = 25.0f * sinf(animationTime * 2.0f);
    float lowerLegBend = fmaxf(0.0f, -30.0f * sinf(animationTime * 2.0f));

    // Left leg leads, right leg follows
    drawPerson.setLeftLegRotation(legSwing, lowerLegBend);
    drawPerson.setRightLegRotation(-legSwing, fmaxf(0.0f, 30.0f * sinf(animationTime * 2.0f)));

    // Natural front-to-back arm swinging (opposite to legs)
    // Upper arm swings forward and back (X-axis rotation) - more forward range
    float upperArmSwing = -30.0f * sinf(animationTime * 2.0f);

    // Lower arm (forearm) moves MORE than upper arm - much more forward movement
    float forearmBend = -40.0f * sinf(animationTime * 2.0f + static_cast<float>(M_PI) * 0.3f);
    float armSwayZ = 10.0f * sinf(animationTime * 2.0f);

    // Left arm swings forward when right leg is forward (opposite coordination)
    // Parameters: (upperX=front-to-back, upperZ=side-to-side, forearmX=forearm bend)
    drawPerson.setLeftArmRotation(upperArmSwing, armSwayZ, forearmBend);
    drawPerson.setRightArmRotation(-upperArmSwing, -armSwayZ, forearmBend);

    // Slight torso sway and head bob for realism - ADD to base rotation
    float animationSway = 2.0f * sinf(animationTime * 2.0f);
    drawPerson.setTorsoRotation(baseTorsoRotation + animationSway);
    drawPerson.setHeadRotation(1.5f * sinf(animationTime * 2.0f), 0.0f);

    float verticalBob = 0.1f * fabsf(sinf(animationTime * 2.0f));
    drawPerson.setJumpHeight(verticalBob);
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
    // Breakdance routine with smoother transitions
    float cycleTime = fmodf(animationTime, 6.0f); // 6-second cycle

    if (cycleTime < 1.0f) {
        // Drop into a crouch while planting hands
        float t = cycleTime;
        drawPerson.setLeftLegRotation(-25.0f * t, 50.0f * t);
        drawPerson.setRightLegRotation(25.0f * t, 50.0f * t);
        drawPerson.setLeftArmRotation(-90.0f * t, 0.0f, -60.0f * t);
        drawPerson.setRightArmRotation(-90.0f * t, 0.0f, -60.0f * t);
        drawPerson.setTorsoRotation(-10.0f * t);
    } else if (cycleTime < 3.0f) {
        // Spin supported by arms with legs extended
        float t = (cycleTime - 1.0f) / 2.0f; // 0..1
        drawPerson.setLeftArmRotation(-90.0f, 0.0f, -60.0f);
        drawPerson.setRightArmRotation(-90.0f, 0.0f, -60.0f);
        float spinAngle = 360.0f * t;
        drawPerson.setTorsoRotation(spinAngle);
        float legKick = 60.0f * sinf(t * static_cast<float>(M_PI));
        drawPerson.setLeftLegRotation(-40.0f + legKick, 0.0f);
        drawPerson.setRightLegRotation(40.0f - legKick, 0.0f);
    } else if (cycleTime < 4.0f) {
        // Freeze pose after the spin
        drawPerson.setLeftArmRotation(-80.0f, -20.0f, -40.0f);
        drawPerson.setRightArmRotation(-100.0f, 20.0f, -40.0f);
        drawPerson.setLeftLegRotation(20.0f, 10.0f);
        drawPerson.setRightLegRotation(-20.0f, 10.0f);
        drawPerson.setTorsoRotation(360.0f);
    } else if (cycleTime < 5.0f) {
        // Quick leg sweeps while staying low
        float t = cycleTime - 4.0f;
        float sweep = 45.0f * sinf(t * static_cast<float>(M_PI) * 2.0f);
        drawPerson.setLeftArmRotation(-80.0f, -20.0f, -40.0f);
        drawPerson.setRightArmRotation(-100.0f, 20.0f, -40.0f);
        drawPerson.setLeftLegRotation(sweep, 0.0f);
        drawPerson.setRightLegRotation(-sweep, 0.0f);
        drawPerson.setTorsoRotation(360.0f);
    } else {
        // Return to standing with small bounce
        float t = cycleTime - 5.0f;
        drawPerson.setLeftArmRotation(-90.0f + 90.0f * t, 0.0f, -60.0f + 60.0f * t);
        drawPerson.setRightArmRotation(-90.0f + 90.0f * t, 0.0f, -60.0f + 60.0f * t);
        drawPerson.setLeftLegRotation(0.0f, 50.0f * (1.0f - t));
        drawPerson.setRightLegRotation(0.0f, 50.0f * (1.0f - t));
        drawPerson.setTorsoRotation(360.0f * (1.0f - t));
    }

    // Continuous bounce and head movement for rhythm
    drawPerson.setJumpHeight(0.05f * sinf(animationTime * 6.0f));
    drawPerson.setHeadRotation(5.0f * sinf(animationTime * 3.0f), 3.0f * cosf(animationTime * 2.0f));
}

void AnimationManager::updateKungFuAnimation() {
    // More natural kung fu routine with weight shifts and smoother transitions
    float cycleTime = fmodf(animationTime, 4.0f); // 4-second cycle

    if (cycleTime < 0.5f) {
        // Guard stance with a tiny bounce
        float t = cycleTime / 0.5f;
        drawPerson.setLeftArmRotation(-45.0f, -25.0f, -15.0f);
        drawPerson.setRightArmRotation(-45.0f, 25.0f, 15.0f);
        drawPerson.setLeftLegRotation(-10.0f * t, 0.0f);
        drawPerson.setRightLegRotation(10.0f * t, 0.0f);
        drawPerson.setTorsoRotation(-5.0f);
    } else if (cycleTime < 1.0f) {
        // Step forward into a right punch
        float t = (cycleTime - 0.5f) / 0.5f;
        drawPerson.setLeftArmRotation(-45.0f + 10.0f * t, -25.0f, -15.0f);
        drawPerson.setRightArmRotation(-45.0f - 80.0f * t, 25.0f, 15.0f * (1.0f - t));
        drawPerson.setLeftLegRotation(-10.0f + 15.0f * t, 0.0f);
        drawPerson.setRightLegRotation(10.0f - 10.0f * t, 0.0f);
        drawPerson.setTorsoRotation(-5.0f + 20.0f * t);
    } else if (cycleTime < 1.5f) {
        // Recover to guard while stepping back
        float t = (cycleTime - 1.0f) / 0.5f;
        drawPerson.setLeftArmRotation(-45.0f + 5.0f * t, -25.0f, -15.0f);
        drawPerson.setRightArmRotation(-125.0f + 80.0f * t, 25.0f, 15.0f * t);
        drawPerson.setLeftLegRotation(5.0f - 15.0f * t, 0.0f);
        drawPerson.setRightLegRotation(0.0f + 10.0f * t, 0.0f);
        drawPerson.setTorsoRotation(15.0f - 10.0f * t);
    } else if (cycleTime < 2.0f) {
        // Step forward into a left punch
        float t = (cycleTime - 1.5f) / 0.5f;
        drawPerson.setLeftArmRotation(-45.0f - 80.0f * t, -25.0f, -15.0f);
        drawPerson.setRightArmRotation(-45.0f + 10.0f * t, 25.0f, 15.0f);
        drawPerson.setLeftLegRotation(-10.0f + 10.0f * t, 0.0f);
        drawPerson.setRightLegRotation(10.0f - 15.0f * t, 0.0f);
        drawPerson.setTorsoRotation(5.0f - 20.0f * t);
    } else if (cycleTime < 2.5f) {
        // Lower stance preparing for kick
        float t = (cycleTime - 2.0f) / 0.5f;
        drawPerson.setLeftArmRotation(-30.0f, -40.0f, -25.0f);
        drawPerson.setRightArmRotation(-30.0f, 40.0f, 25.0f);
        drawPerson.setLeftLegRotation(-10.0f - 10.0f * t, -5.0f - 5.0f * t);
        drawPerson.setRightLegRotation(-10.0f - 10.0f * t, -5.0f - 5.0f * t);
        drawPerson.setTorsoRotation(-5.0f * t);
    } else if (cycleTime < 3.0f) {
        // High kick with body lean
        float t = (cycleTime - 2.5f) / 0.5f;
        drawPerson.setLeftArmRotation(-30.0f + 15.0f * t, -40.0f, -25.0f);
        drawPerson.setRightArmRotation(-30.0f - 15.0f * t, 40.0f, 25.0f);
        drawPerson.setLeftLegRotation(-20.0f, -10.0f);
        drawPerson.setRightLegRotation(-20.0f + 120.0f * t, -10.0f + 20.0f * t);
        drawPerson.setTorsoRotation(-5.0f - 10.0f * t);
    } else if (cycleTime < 3.5f) {
        // Block after the kick
        float t = (cycleTime - 3.0f) / 0.5f;
        drawPerson.setLeftArmRotation(-90.0f + 20.0f * t, -20.0f, -45.0f + 5.0f * t);
        drawPerson.setRightArmRotation(-90.0f + 20.0f * t, 20.0f, 45.0f - 5.0f * t);
        drawPerson.setLeftLegRotation(-15.0f + 10.0f * t, 0.0f);
        drawPerson.setRightLegRotation(-15.0f + 10.0f * t, 0.0f);
        drawPerson.setTorsoRotation(-5.0f * (1.0f - t));
    } else {
        // Return to fighting stance with slight bounce
        float t = (cycleTime - 3.5f) / 0.5f;
        drawPerson.setLeftArmRotation(-45.0f, -30.0f, -20.0f);
        drawPerson.setRightArmRotation(-45.0f, 30.0f, 20.0f);
        drawPerson.setLeftLegRotation(-10.0f + 5.0f * sinf(t * static_cast<float>(M_PI) * 2.0f), 0.0f);
        drawPerson.setRightLegRotation(10.0f - 5.0f * sinf(t * static_cast<float>(M_PI) * 2.0f), 0.0f);
        drawPerson.setTorsoRotation(-5.0f);
    }

    // Subtle head focus and bounce
    drawPerson.setHeadRotation(2.5f * sinf(animationTime * 1.2f), 3.0f * cosf(animationTime));
    drawPerson.setJumpHeight(0.05f * fabsf(sinf(animationTime * 4.0f)));
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
