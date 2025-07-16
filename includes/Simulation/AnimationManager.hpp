#pragma once

#include "../humangl.hpp"
#include "../Human/DrawPerson.hpp"

class AnimationManager {
private:
    DrawPerson& drawPerson;
    
    // Animation state
    AnimationMode currentAnimation;
    float animationTime;
    float jumpHeight;
    float baseTorsoRotation; // User's base rotation that animations add to
    
    // Animation parameters
    static constexpr float ANIMATION_SPEED = 0.05f;
    static constexpr float JUMP_DURATION = 2.0f;
    static constexpr float JUMP_MAX_HEIGHT = 2.0f;

public:
    AnimationManager(DrawPerson& person);
    ~AnimationManager() = default;

    // Main update method
    void update();
    
    // Animation control methods
    void startWalking();
    void startJumping();
    void startDancing();
    void startKungFu();
    void stopAnimation();
    
    // Animation update methods
    void updateWalkingAnimation();
    void updateJumpingAnimation();
    void updateDancingAnimation();
    void updateKungFuAnimation();
    
    // Reset methods
    void resetLimbPositions();
    void resetAnimationTime();
    void resetToDefaultPosition();

    // Torso rotation management
    void updateBaseTorsoRotation();
    
    // Getters
    AnimationMode getCurrentAnimation() const { return currentAnimation; }
    float getAnimationTime() const { return animationTime; }
    float getJumpHeight() const { return jumpHeight; }
    
    // Setters
    void setCurrentAnimation(AnimationMode mode) { currentAnimation = mode; }
    void setAnimationTime(float time) { animationTime = time; }
    void setJumpHeight(float height) { jumpHeight = height; }
    
    // State queries
    bool isAnimating() const { return currentAnimation != NONE; }
    bool isWalking() const { return currentAnimation == WALKING; }
    bool isJumping() const { return currentAnimation == JUMPING; }
    bool isDancing() const { return currentAnimation == DANCING; }
    bool isKungFu() const { return currentAnimation == KUNGFU; }
};
