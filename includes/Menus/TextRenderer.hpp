#pragma once

#include "../humangl.hpp"

class TextRenderer {
private:
    int fontSize;
    
    // Draw individual characters using line segments
    void drawSimpleChar(char c, float x, float y, float width, float height);

    // Modular character drawing functions
    void drawAlphabet(char c, float cx, float y, float w, float h);
    void drawNumber(char c, float cx, float y, float w, float h);
    void drawSymbol(char c, float cx, float y, float w, float h);

public:
    TextRenderer();
    ~TextRenderer();
    
    // Initialize text system
    bool initialize();
    
    // Clean up resources
    void cleanup();
    
    // Get text dimensions for layout calculations
    void getTextSize(const std::string& text, int* width, int* height);
    
    // Draw text at specified position with color
    void drawText(float x, float y, const std::string& text, float r = 1.0f, float g = 1.0f, float b = 1.0f);
};
