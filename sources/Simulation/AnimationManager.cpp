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
    float legSwing = HUMANGL_WALK_LEG_SWING_AMPLITUDE * sinf(animationTime * HUMANGL_WALK_ANIMATION_FREQUENCY);
    float lowerLegBend = fmaxf(0.0f, -HUMANGL_WALK_LOWER_LEG_BEND_AMPLITUDE * sinf(animationTime * HUMANGL_WALK_ANIMATION_FREQUENCY));

    // Left leg leads, right leg follows
    drawPerson.setLeftLegRotation(legSwing, lowerLegBend);
    drawPerson.setRightLegRotation(-legSwing, fmaxf(0.0f, HUMANGL_WALK_LOWER_LEG_BEND_AMPLITUDE * sinf(animationTime * HUMANGL_WALK_ANIMATION_FREQUENCY)));

    // Natural front-to-back arm swinging (opposite to legs)
    // Upper arm swings forward and back (X-axis rotation) - more forward range
    float upperArmSwing = -HUMANGL_WALK_ARM_SWING_AMPLITUDE * sinf(animationTime * HUMANGL_WALK_ANIMATION_FREQUENCY);

    // Lower arm (forearm) moves MORE than upper arm - much more forward movement
    float forearmBend = -HUMANGL_WALK_FOREARM_BEND_AMPLITUDE * sinf(animationTime * HUMANGL_WALK_ANIMATION_FREQUENCY + static_cast<float>(M_PI) * HUMANGL_WALK_FOREARM_PHASE_OFFSET);
    float armSwayZ = HUMANGL_WALK_ARM_SWAY_AMPLITUDE * sinf(animationTime * HUMANGL_WALK_ANIMATION_FREQUENCY);

    // Left arm swings forward when right leg is forward (opposite coordination)
    // Parameters: (upperX=front-to-back, upperZ=side-to-side, forearmX=forearm bend)
    drawPerson.setLeftArmRotation(upperArmSwing, armSwayZ, forearmBend);
    drawPerson.setRightArmRotation(-upperArmSwing, -armSwayZ, forearmBend);

    // Slight torso sway and head bob for realism - ADD to base rotation
    float animationSway = HUMANGL_WALK_TORSO_SWAY_AMPLITUDE * sinf(animationTime * HUMANGL_WALK_ANIMATION_FREQUENCY);
    drawPerson.setTorsoRotation(baseTorsoRotation + animationSway);
    drawPerson.setHeadRotation(HUMANGL_WALK_HEAD_BOB_AMPLITUDE * sinf(animationTime * HUMANGL_WALK_ANIMATION_FREQUENCY), 0.0f);

    float verticalBob = HUMANGL_WALK_VERTICAL_BOB_AMPLITUDE * fabsf(sinf(animationTime * HUMANGL_WALK_ANIMATION_FREQUENCY));
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
    float cycleTime = fmodf(animationTime, HUMANGL_DANCING_CYCLE_DURATION); // 6-second cycle

    if (cycleTime < 1.0f) {
        // Drop into a crouch while planting hands
        float t = cycleTime;
        drawPerson.setLeftLegRotation(-HUMANGL_DANCE_CROUCH_LEG_ANGLE * t, HUMANGL_DANCE_CROUCH_LEG_BEND * t);
        drawPerson.setRightLegRotation(HUMANGL_DANCE_CROUCH_LEG_ANGLE * t, HUMANGL_DANCE_CROUCH_LEG_BEND * t);
        drawPerson.setLeftArmRotation(-HUMANGL_DANCE_ARM_PLANT_ANGLE * t, 0.0f, -HUMANGL_DANCE_ARM_PLANT_FOREARM * t);
        drawPerson.setRightArmRotation(-HUMANGL_DANCE_ARM_PLANT_ANGLE * t, 0.0f, -HUMANGL_DANCE_ARM_PLANT_FOREARM * t);
        float animationRotation = -HUMANGL_DANCE_TORSO_CROUCH_ANGLE * t;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    } else if (cycleTime < 3.0f) {
        // Spin supported by arms with legs extended
        float t = (cycleTime - 1.0f) / 2.0f; // 0..1
        drawPerson.setLeftArmRotation(-HUMANGL_DANCE_ARM_PLANT_ANGLE, 0.0f, -HUMANGL_DANCE_ARM_PLANT_FOREARM);
        drawPerson.setRightArmRotation(-HUMANGL_DANCE_ARM_PLANT_ANGLE, 0.0f, -HUMANGL_DANCE_ARM_PLANT_FOREARM);
        float animationRotation = HUMANGL_DANCE_SPIN_ANGLE * t;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
        float legKick = HUMANGL_DANCE_LEG_KICK_AMPLITUDE * sinf(t * static_cast<float>(M_PI));
        drawPerson.setLeftLegRotation(-HUMANGL_DANCE_LEG_KICK_BASE + legKick, 0.0f);
        drawPerson.setRightLegRotation(HUMANGL_DANCE_LEG_KICK_BASE - legKick, 0.0f);
    } else if (cycleTime < 4.0f) {
        // Freeze pose after the spin
        drawPerson.setLeftArmRotation(-HUMANGL_DANCE_FREEZE_ARM_ANGLE_L, -HUMANGL_DANCE_FREEZE_ARM_SPREAD, -HUMANGL_DANCE_FREEZE_ARM_FOREARM);
        drawPerson.setRightArmRotation(-HUMANGL_DANCE_FREEZE_ARM_ANGLE_R, HUMANGL_DANCE_FREEZE_ARM_SPREAD, -HUMANGL_DANCE_FREEZE_ARM_FOREARM);
        drawPerson.setLeftLegRotation(HUMANGL_DANCE_FREEZE_LEG_ANGLE, HUMANGL_DANCE_FREEZE_LEG_BEND);
        drawPerson.setRightLegRotation(-HUMANGL_DANCE_FREEZE_LEG_ANGLE, HUMANGL_DANCE_FREEZE_LEG_BEND);
        float animationRotation = HUMANGL_DANCE_SPIN_ANGLE;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    } else if (cycleTime < 5.0f) {
        // Quick leg sweeps while staying low
        float t = cycleTime - 4.0f;
        float sweep = HUMANGL_DANCE_SWEEP_AMPLITUDE * sinf(t * static_cast<float>(M_PI) * 2.0f);
        drawPerson.setLeftArmRotation(-HUMANGL_DANCE_FREEZE_ARM_ANGLE_L, -HUMANGL_DANCE_FREEZE_ARM_SPREAD, -HUMANGL_DANCE_FREEZE_ARM_FOREARM);
        drawPerson.setRightArmRotation(-HUMANGL_DANCE_FREEZE_ARM_ANGLE_R, HUMANGL_DANCE_FREEZE_ARM_SPREAD, -HUMANGL_DANCE_FREEZE_ARM_FOREARM);
        drawPerson.setLeftLegRotation(sweep, 0.0f);
        drawPerson.setRightLegRotation(-sweep, 0.0f);
        float animationRotation = HUMANGL_DANCE_SPIN_ANGLE;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    } else {
        // Return to standing with small bounce
        float t = cycleTime - 5.0f;
        drawPerson.setLeftArmRotation(-HUMANGL_DANCE_ARM_PLANT_ANGLE + HUMANGL_DANCE_ARM_PLANT_ANGLE * t, 0.0f, -HUMANGL_DANCE_ARM_PLANT_FOREARM + HUMANGL_DANCE_ARM_PLANT_FOREARM * t);
        drawPerson.setRightArmRotation(-HUMANGL_DANCE_ARM_PLANT_ANGLE + HUMANGL_DANCE_ARM_PLANT_ANGLE * t, 0.0f, -HUMANGL_DANCE_ARM_PLANT_FOREARM + HUMANGL_DANCE_ARM_PLANT_FOREARM * t);
        drawPerson.setLeftLegRotation(0.0f, HUMANGL_DANCE_CROUCH_LEG_BEND * (1.0f - t));
        drawPerson.setRightLegRotation(0.0f, HUMANGL_DANCE_CROUCH_LEG_BEND * (1.0f - t));
        float animationRotation = HUMANGL_DANCE_SPIN_ANGLE * (1.0f - t);
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    }

    // Continuous bounce and head movement for rhythm
    drawPerson.setJumpHeight(HUMANGL_DANCE_BOUNCE_AMPLITUDE * sinf(animationTime * HUMANGL_DANCE_RHYTHM_FREQUENCY));
    drawPerson.setHeadRotation(HUMANGL_DANCE_HEAD_X_AMPLITUDE * sinf(animationTime * HUMANGL_DANCE_HEAD_X_FREQUENCY), HUMANGL_DANCE_HEAD_Y_AMPLITUDE * cosf(animationTime * HUMANGL_DANCE_HEAD_Y_FREQUENCY));
}

void AnimationManager::updateKungFuAnimation() {
    // More natural kung fu routine with weight shifts and smoother transitions
    float cycleTime = fmodf(animationTime, HUMANGL_KUNGFU_CYCLE_DURATION); // 4-second cycle

    if (cycleTime < HUMANGL_KUNGFU_GUARD_STANCE_DURATION) {
        // Guard stance with a tiny bounce
        float t = cycleTime / HUMANGL_KUNGFU_GUARD_STANCE_DURATION;
        drawPerson.setLeftArmRotation(-HUMANGL_KUNGFU_ARM_GUARD_ANGLE, -HUMANGL_KUNGFU_ARM_GUARD_SPREAD, -HUMANGL_KUNGFU_ARM_GUARD_FOREARM);
        drawPerson.setRightArmRotation(-HUMANGL_KUNGFU_ARM_GUARD_ANGLE, HUMANGL_KUNGFU_ARM_GUARD_SPREAD, HUMANGL_KUNGFU_ARM_GUARD_FOREARM);
        drawPerson.setLeftLegRotation(-HUMANGL_KUNGFU_LEG_STANCE_ANGLE * t, 0.0f);
        drawPerson.setRightLegRotation(HUMANGL_KUNGFU_LEG_STANCE_ANGLE * t, 0.0f);
        float animationRotation = -HUMANGL_KUNGFU_TORSO_LEAN_ANGLE;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    } else if (cycleTime < 1.0f) {
        // Step forward into a right punch
        float t = (cycleTime - HUMANGL_KUNGFU_GUARD_STANCE_DURATION) / HUMANGL_KUNGFU_PUNCH_DURATION;
        drawPerson.setLeftArmRotation(-HUMANGL_KUNGFU_ARM_GUARD_ANGLE + 10.0f * t, -HUMANGL_KUNGFU_ARM_GUARD_SPREAD, -HUMANGL_KUNGFU_ARM_GUARD_FOREARM);
        drawPerson.setRightArmRotation(-HUMANGL_KUNGFU_ARM_GUARD_ANGLE - HUMANGL_KUNGFU_PUNCH_EXTENSION * t, HUMANGL_KUNGFU_ARM_GUARD_SPREAD, HUMANGL_KUNGFU_ARM_GUARD_FOREARM * (1.0f - t));
        drawPerson.setLeftLegRotation(-HUMANGL_KUNGFU_LEG_STANCE_ANGLE + 15.0f * t, 0.0f);
        drawPerson.setRightLegRotation(HUMANGL_KUNGFU_LEG_STANCE_ANGLE - HUMANGL_KUNGFU_LEG_STANCE_ANGLE * t, 0.0f);
        float animationRotation = -HUMANGL_KUNGFU_TORSO_LEAN_ANGLE + 20.0f * t;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    } else if (cycleTime < 1.5f) {
        // Recover to guard while stepping back
        float t = (cycleTime - 1.0f) / HUMANGL_KUNGFU_RECOVERY_DURATION;
        drawPerson.setLeftArmRotation(-HUMANGL_KUNGFU_ARM_GUARD_ANGLE + 5.0f * t, -HUMANGL_KUNGFU_ARM_GUARD_SPREAD, -HUMANGL_KUNGFU_ARM_GUARD_FOREARM);
        drawPerson.setRightArmRotation(-125.0f + HUMANGL_KUNGFU_PUNCH_EXTENSION * t, HUMANGL_KUNGFU_ARM_GUARD_SPREAD, HUMANGL_KUNGFU_ARM_GUARD_FOREARM * t);
        drawPerson.setLeftLegRotation(5.0f - 15.0f * t, 0.0f);
        drawPerson.setRightLegRotation(0.0f + HUMANGL_KUNGFU_LEG_STANCE_ANGLE * t, 0.0f);
        float animationRotation = 15.0f - 10.0f * t;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    } else if (cycleTime < 2.0f) {
        // Step forward into a left punch
        float t = (cycleTime - 1.5f) / 0.5f;
        drawPerson.setLeftArmRotation(-45.0f - 80.0f * t, -25.0f, -15.0f);
        drawPerson.setRightArmRotation(-45.0f + 10.0f * t, 25.0f, 15.0f);
        drawPerson.setLeftLegRotation(-10.0f + 10.0f * t, 0.0f);
        drawPerson.setRightLegRotation(10.0f - 15.0f * t, 0.0f);
        float animationRotation = 5.0f - 20.0f * t;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    } else if (cycleTime < 2.5f) {
        // Lower stance preparing for kick
        float t = (cycleTime - 2.0f) / 0.5f;
        drawPerson.setLeftArmRotation(-30.0f, -40.0f, -25.0f);
        drawPerson.setRightArmRotation(-30.0f, 40.0f, 25.0f);
        drawPerson.setLeftLegRotation(-10.0f - 10.0f * t, -5.0f - 5.0f * t);
        drawPerson.setRightLegRotation(-10.0f - 10.0f * t, -5.0f - 5.0f * t);
        float animationRotation = -5.0f * t;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    } else if (cycleTime < 3.0f) {
        // High kick with body lean
        float t = (cycleTime - 2.5f) / 0.5f;
        drawPerson.setLeftArmRotation(-30.0f + 15.0f * t, -40.0f, -25.0f);
        drawPerson.setRightArmRotation(-30.0f - 15.0f * t, 40.0f, 25.0f);
        drawPerson.setLeftLegRotation(-20.0f, -10.0f);
        drawPerson.setRightLegRotation(-20.0f + 120.0f * t, -10.0f + 20.0f * t);
        float animationRotation = -5.0f - 10.0f * t;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    } else if (cycleTime < 3.5f) {
        // Block after the kick
        float t = (cycleTime - 3.0f) / 0.5f;
        drawPerson.setLeftArmRotation(-90.0f + 20.0f * t, -20.0f, -45.0f + 5.0f * t);
        drawPerson.setRightArmRotation(-90.0f + 20.0f * t, 20.0f, 45.0f - 5.0f * t);
        drawPerson.setLeftLegRotation(-15.0f + 10.0f * t, 0.0f);
        drawPerson.setRightLegRotation(-15.0f + 10.0f * t, 0.0f);
        float animationRotation = -5.0f * (1.0f - t);
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    } else {
        // Return to fighting stance with slight bounce
        float t = (cycleTime - 3.5f) / 0.5f;
        drawPerson.setLeftArmRotation(-45.0f, -30.0f, -20.0f);
        drawPerson.setRightArmRotation(-45.0f, 30.0f, 20.0f);
        drawPerson.setLeftLegRotation(-10.0f + 5.0f * sinf(t * static_cast<float>(M_PI) * 2.0f), 0.0f);
        drawPerson.setRightLegRotation(10.0f - 5.0f * sinf(t * static_cast<float>(M_PI) * 2.0f), 0.0f);
        float animationRotation = -5.0f;
        drawPerson.setTorsoRotation(baseTorsoRotation + animationRotation);
    }

    // Subtle head focus and bounce
    drawPerson.setHeadRotation(HUMANGL_KUNGFU_HEAD_FOCUS_X * sinf(animationTime * HUMANGL_KUNGFU_HEAD_X_FREQUENCY), HUMANGL_KUNGFU_HEAD_FOCUS_Y * cosf(animationTime * HUMANGL_KUNGFU_HEAD_Y_FREQUENCY));
    drawPerson.setJumpHeight(HUMANGL_KUNGFU_BOUNCE_AMPLITUDE * fabsf(sinf(animationTime * HUMANGL_KUNGFU_BOUNCE_FREQUENCY)));
}

void AnimationManager::resetLimbPositions() {
    drawPerson.setLeftLegRotation(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    drawPerson.setRightLegRotation(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    drawPerson.setLeftArmRotation(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    drawPerson.setRightArmRotation(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    drawPerson.setHeadRotation(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    drawPerson.setJumpHeight(HUMANGL_OPENGL_AXIS_NONE);
}

void AnimationManager::resetAnimationTime() {
    animationTime = HUMANGL_OPENGL_AXIS_NONE;
    jumpHeight = HUMANGL_OPENGL_AXIS_NONE;
}

void AnimationManager::resetToDefaultPosition() {
    // Stop any current animation
    currentAnimation = NONE;

    // Reset all limb positions to default
    resetLimbPositions();
    resetAnimationTime();

    // Reset torso rotation to face forward
    baseTorsoRotation = HUMANGL_OPENGL_AXIS_NONE;
    drawPerson.setTorsoRotation(HUMANGL_OPENGL_AXIS_NONE);
}

void AnimationManager::updateBaseTorsoRotation() {
    // Update base torso rotation from current DrawPerson state
    // This preserves user input during animations
    baseTorsoRotation = drawPerson.getTorsoRotation();
}
