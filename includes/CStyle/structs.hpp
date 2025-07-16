#pragma once

#include "libs.hpp"
#include "enums.hpp"

// Menu button structure (moved from MenuTypes.hpp)
struct MenuButton {
    float x, y, width, height;
    std::string text;
    bool hovered;

    MenuButton(float px, float py, float w, float h, const std::string& txt)
        : x(px), y(py), width(w), height(h), text(txt), hovered(false) {}

    bool isPointInside(float px, float py) const {
        return px >= x && px <= x + width && py >= y && py <= y + height;
    }
};

// Color structure (RGB + Alpha)
struct Color {
    float r, g, b, a;
    
    Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
    Color(float red, float green, float blue, float alpha = 1.0f) 
        : r(red), g(green), b(blue), a(alpha) {}
    
    // Predefined colors
    static Color White() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
    static Color Black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
    static Color Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
    static Color Green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
    static Color Blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
    static Color Yellow() { return Color(1.0f, 1.0f, 0.0f, 1.0f); }
    static Color Magenta() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }
    static Color Cyan() { return Color(0.0f, 1.0f, 1.0f, 1.0f); }
    static Color SkinTone() { return Color(0.9f, 0.7f, 0.6f, 1.0f); }
    static Color ClothingBlue() { return Color(0.2f, 0.4f, 0.8f, 1.0f); }
};

// 3D Vector structure
struct Vector3 {
    float x, y, z;
    
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float px, float py, float pz) : x(px), y(py), z(pz) {}
    
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    
    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    Vector3 normalized() const {
        float len = length();
        if (len > 0.0f) {
            return Vector3(x / len, y / len, z / len);
        }
        return Vector3();
    }
};

// Body part settings structure
struct BodyPartSettings {
    Color color;
    Vector3 scale;
    Vector3 rotation;
    Vector3 position;
    bool visible;
    
    BodyPartSettings() 
        : color(Color::SkinTone()), scale(1.0f, 1.0f, 1.0f), 
          rotation(0.0f, 0.0f, 0.0f), position(0.0f, 0.0f, 0.0f), visible(true) {}
    
    BodyPartSettings(const Color& col, const Vector3& scl = Vector3(1.0f, 1.0f, 1.0f)) 
        : color(col), scale(scl), rotation(0.0f, 0.0f, 0.0f), 
          position(0.0f, 0.0f, 0.0f), visible(true) {}
};

// Animation keyframe structure
struct AnimationKeyframe {
    float time;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    
    AnimationKeyframe() : time(0.0f), position(), rotation(), scale(1.0f, 1.0f, 1.0f) {}
    AnimationKeyframe(float t, const Vector3& pos, const Vector3& rot, const Vector3& scl = Vector3(1.0f, 1.0f, 1.0f))
        : time(t), position(pos), rotation(rot), scale(scl) {}
};

// Window settings structure
struct WindowSettings {
    int width, height;
    bool fullscreen;
    bool vsync;
    std::string title;
    
    WindowSettings() 
        : width(800), height(600), fullscreen(false), vsync(true), 
          title("HumanGL - Skeletal Animation") {}
    
    WindowSettings(int w, int h, bool fs = false, bool vs = true, const std::string& t = "HumanGL")
        : width(w), height(h), fullscreen(fs), vsync(vs), title(t) {}
};

// Input state structure
struct InputState {
    bool keys[256];  // SDL key states
    bool mouseButtons[3];  // Left, Right, Middle
    int mouseX, mouseY;
    int mouseDeltaX, mouseDeltaY;
    bool quit;
    
    InputState() : mouseX(0), mouseY(0), mouseDeltaX(0), mouseDeltaY(0), quit(false) {
        std::memset(keys, 0, sizeof(keys));
        std::memset(mouseButtons, 0, sizeof(mouseButtons));
    }
};

// Performance metrics structure
struct PerformanceMetrics {
    float frameTime;
    float fps;
    int frameCount;
    std::chrono::high_resolution_clock::time_point lastTime;
    
    PerformanceMetrics() : frameTime(0.0f), fps(0.0f), frameCount(0) {
        lastTime = std::chrono::high_resolution_clock::now();
    }
};
