#include "../../includes/Menus/TextRenderer.hpp"

TextRenderer::TextRenderer() : fontSize(16) {
}

TextRenderer::~TextRenderer() {
    cleanup();
}

bool TextRenderer::initialize() {
    fontSize = 16;
    return true;
}

void TextRenderer::cleanup() {
    // Nothing to clean up for simple system
}

void TextRenderer::getTextSize(const std::string& text, int* width, int* height) {
    *width = static_cast<int>(text.length() * 10);  // 10 pixels per character
    *height = 16;  // Fixed height
}

void TextRenderer::drawText(float x, float y, const std::string& text, float r, float g, float b) {
    glColor3f(r, g, b);
    
    float charWidth = 10.0f;
    float charHeight = 16.0f;
    
    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        float charX = x + static_cast<float>(i) * charWidth;
        
        // Draw character using simple shapes
        drawSimpleChar(c, charX, y, charWidth, charHeight);
    }
}

void TextRenderer::drawSimpleChar(char c, float x, float y, float width, float height) {
    c = static_cast<char>(toupper(c));

    glLineWidth(2.0f);
    glBegin(GL_LINES);

    float w = width * 0.8f;  // Use 80% of width for character
    float h = height;
    float cx = x + width * 0.1f;  // Center the character

    // Route to appropriate drawing function based on character type
    if (c >= 'A' && c <= 'Z') {
        drawAlphabet(c, cx, y, w, h);
    } else if (c >= '0' && c <= '9') {
        drawNumber(c, cx, y, w, h);
    } else {
        drawSymbol(c, cx, y, w, h);
    }

    glEnd();
}

void TextRenderer::drawAlphabet(char c, float cx, float y, float w, float h) {
    switch (c) {
        case 'A':
            // Triangle top
            glVertex2f(cx + w/2, y);
            glVertex2f(cx, y + h);
            glVertex2f(cx + w/2, y);
            glVertex2f(cx + w, y + h);
            // Cross bar
            glVertex2f(cx + w*0.25f, y + h*0.6f);
            glVertex2f(cx + w*0.75f, y + h*0.6f);
            break;
        case 'B':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w*0.7f, y);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w*0.7f, y + h/2);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w*0.7f, y + h);
            // Top right curve (simplified)
            glVertex2f(cx + w*0.7f, y);
            glVertex2f(cx + w*0.7f, y + h/2);
            // Bottom right curve (simplified)
            glVertex2f(cx + w*0.7f, y + h/2);
            glVertex2f(cx + w*0.7f, y + h);
            break;
        case 'C':
            // Left vertical
            glVertex2f(cx, y + h*0.2f);
            glVertex2f(cx, y + h*0.8f);
            // Top horizontal
            glVertex2f(cx, y + h*0.2f);
            glVertex2f(cx + w*0.8f, y + h*0.2f);
            // Bottom horizontal
            glVertex2f(cx, y + h*0.8f);
            glVertex2f(cx + w*0.8f, y + h*0.8f);
            break;
        case 'D':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w*0.7f, y);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w*0.7f, y + h);
            // Right curve (simplified)
            glVertex2f(cx + w*0.7f, y);
            glVertex2f(cx + w*0.7f, y + h);
            break;
        case 'E':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w*0.8f, y);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w*0.6f, y + h/2);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w*0.8f, y + h);
            break;
        case 'F':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w*0.8f, y);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w*0.6f, y + h/2);
            break;
        case 'G':
            // Left vertical
            glVertex2f(cx, y + h*0.2f);
            glVertex2f(cx, y + h*0.8f);
            // Top horizontal
            glVertex2f(cx, y + h*0.2f);
            glVertex2f(cx + w*0.8f, y + h*0.2f);
            // Bottom horizontal
            glVertex2f(cx, y + h*0.8f);
            glVertex2f(cx + w*0.8f, y + h*0.8f);
            // Right vertical (bottom half)
            glVertex2f(cx + w*0.8f, y + h/2);
            glVertex2f(cx + w*0.8f, y + h*0.8f);
            // Middle horizontal (right side)
            glVertex2f(cx + w*0.5f, y + h/2);
            glVertex2f(cx + w*0.8f, y + h/2);
            break;
        case 'H':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Right vertical
            glVertex2f(cx + w, y);
            glVertex2f(cx + w, y + h);
            // Cross bar
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w, y + h/2);
            break;
        case 'I':
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y);
            // Middle vertical
            glVertex2f(cx + w/2, y);
            glVertex2f(cx + w/2, y + h);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w, y + h);
            break;
        case 'J':
            // Top horizontal
            glVertex2f(cx + w*0.3f, y);
            glVertex2f(cx + w, y);
            // Right vertical
            glVertex2f(cx + w*0.7f, y);
            glVertex2f(cx + w*0.7f, y + h*0.8f);
            // Bottom curve (simplified as lines)
            glVertex2f(cx + w*0.7f, y + h*0.8f);
            glVertex2f(cx + w*0.3f, y + h);
            glVertex2f(cx + w*0.3f, y + h);
            glVertex2f(cx, y + h*0.8f);
            glVertex2f(cx, y + h*0.8f);
            glVertex2f(cx, y + h*0.6f);
            break;
        case 'K':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Upper diagonal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w, y);
            // Lower diagonal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w, y + h);
            break;
        case 'L':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w*0.8f, y + h);
            break;
        case 'M':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Right vertical
            glVertex2f(cx + w, y);
            glVertex2f(cx + w, y + h);
            // Left diagonal
            glVertex2f(cx, y);
            glVertex2f(cx + w/2, y + h/2);
            // Right diagonal
            glVertex2f(cx + w/2, y + h/2);
            glVertex2f(cx + w, y);
            break;
        case 'N':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Right vertical
            glVertex2f(cx + w, y);
            glVertex2f(cx + w, y + h);
            // Diagonal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w, y);
            break;
        case 'O':
            // Left vertical
            glVertex2f(cx, y + h*0.2f);
            glVertex2f(cx, y + h*0.8f);
            // Right vertical
            glVertex2f(cx + w, y + h*0.2f);
            glVertex2f(cx + w, y + h*0.8f);
            // Top horizontal
            glVertex2f(cx, y + h*0.2f);
            glVertex2f(cx + w, y + h*0.2f);
            // Bottom horizontal
            glVertex2f(cx, y + h*0.8f);
            glVertex2f(cx + w, y + h*0.8f);
            break;
        case 'P':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w*0.8f, y);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w*0.8f, y + h/2);
            // Right vertical (top half)
            glVertex2f(cx + w*0.8f, y);
            glVertex2f(cx + w*0.8f, y + h/2);
            break;
        case 'Q':
            // Left vertical
            glVertex2f(cx, y + h*0.2f);
            glVertex2f(cx, y + h*0.8f);
            // Right vertical
            glVertex2f(cx + w*0.8f, y + h*0.2f);
            glVertex2f(cx + w*0.8f, y + h*0.8f);
            // Top horizontal
            glVertex2f(cx + w*0.2f, y);
            glVertex2f(cx + w*0.6f, y);
            // Bottom horizontal
            glVertex2f(cx + w*0.2f, y + h);
            glVertex2f(cx + w*0.6f, y + h);
            // Top curves (approximated with lines)
            glVertex2f(cx, y + h*0.2f);
            glVertex2f(cx + w*0.2f, y);
            glVertex2f(cx + w*0.6f, y);
            glVertex2f(cx + w*0.8f, y + h*0.2f);
            // Bottom curves (approximated with lines)
            glVertex2f(cx, y + h*0.8f);
            glVertex2f(cx + w*0.2f, y + h);
            glVertex2f(cx + w*0.6f, y + h);
            glVertex2f(cx + w*0.8f, y + h*0.8f);
            // Tail diagonal
            glVertex2f(cx + w*0.6f, y + h*0.6f);
            glVertex2f(cx + w*0.9f, y + h*0.9f);
            break;
        case 'R':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w*0.8f, y);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w*0.8f, y + h/2);
            // Right vertical (top half)
            glVertex2f(cx + w*0.8f, y);
            glVertex2f(cx + w*0.8f, y + h/2);
            // Diagonal
            glVertex2f(cx + w*0.5f, y + h/2);
            glVertex2f(cx + w*0.8f, y + h);
            break;
        case 'S':
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w*0.8f, y);
            // Left vertical (top half)
            glVertex2f(cx, y);
            glVertex2f(cx, y + h/2);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w*0.8f, y + h/2);
            // Right vertical (bottom half)
            glVertex2f(cx + w*0.8f, y + h/2);
            glVertex2f(cx + w*0.8f, y + h);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w*0.8f, y + h);
            break;
        case 'T':
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y);
            // Middle vertical
            glVertex2f(cx + w/2, y);
            glVertex2f(cx + w/2, y + h);
            break;
        case 'U':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h*0.8f);
            // Right vertical
            glVertex2f(cx + w, y);
            glVertex2f(cx + w, y + h*0.8f);
            // Bottom horizontal
            glVertex2f(cx, y + h*0.8f);
            glVertex2f(cx + w, y + h*0.8f);
            break;
        case 'V':
            // Left diagonal
            glVertex2f(cx, y);
            glVertex2f(cx + w/2, y + h);
            // Right diagonal
            glVertex2f(cx + w/2, y + h);
            glVertex2f(cx + w, y);
            break;
        case 'W':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx + w*0.2f, y + h);
            // Left middle diagonal
            glVertex2f(cx + w*0.2f, y + h);
            glVertex2f(cx + w*0.5f, y + h*0.6f);
            // Right middle diagonal
            glVertex2f(cx + w*0.5f, y + h*0.6f);
            glVertex2f(cx + w*0.8f, y + h);
            // Right vertical
            glVertex2f(cx + w*0.8f, y + h);
            glVertex2f(cx + w, y);
            break;
        case 'X':
            // Left diagonal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y + h);
            // Right diagonal
            glVertex2f(cx + w, y);
            glVertex2f(cx, y + h);
            break;
        case 'Y':
            // Left diagonal
            glVertex2f(cx, y);
            glVertex2f(cx + w/2, y + h/2);
            // Right diagonal
            glVertex2f(cx + w, y);
            glVertex2f(cx + w/2, y + h/2);
            // Bottom vertical
            glVertex2f(cx + w/2, y + h/2);
            glVertex2f(cx + w/2, y + h);
            break;
        case 'Z':
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y);
            // Diagonal
            glVertex2f(cx + w, y);
            glVertex2f(cx, y + h);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w, y + h);
            break;
        default:
            // Unknown alphabet character - draw a simple box
            glVertex2f(cx, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.7f);
            glVertex2f(cx + w*0.6f, y + h*0.7f);
            glVertex2f(cx, y + h*0.7f);
            glVertex2f(cx, y + h*0.7f);
            glVertex2f(cx, y + h*0.3f);
            break;
    }
}

void TextRenderer::drawNumber(char c, float cx, float y, float w, float h) {
    switch (c) {
        case '0':
            // Oval shape
            glVertex2f(cx, y + h*0.2f);
            glVertex2f(cx, y + h*0.8f);
            glVertex2f(cx + w, y + h*0.2f);
            glVertex2f(cx + w, y + h*0.8f);
            glVertex2f(cx, y + h*0.2f);
            glVertex2f(cx + w, y + h*0.2f);
            glVertex2f(cx, y + h*0.8f);
            glVertex2f(cx + w, y + h*0.8f);
            // Diagonal to distinguish from O
            glVertex2f(cx + w*0.2f, y + h*0.7f);
            glVertex2f(cx + w*0.8f, y + h*0.3f);
            break;
        case '1':
            // Vertical line
            glVertex2f(cx + w/2, y);
            glVertex2f(cx + w/2, y + h);
            // Top diagonal
            glVertex2f(cx + w*0.3f, y + h*0.2f);
            glVertex2f(cx + w/2, y);
            // Bottom horizontal
            glVertex2f(cx + w*0.2f, y + h);
            glVertex2f(cx + w*0.8f, y + h);
            break;
        case '2':
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y);
            // Top right vertical
            glVertex2f(cx + w, y);
            glVertex2f(cx + w, y + h/2);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w, y + h/2);
            // Bottom left vertical
            glVertex2f(cx, y + h/2);
            glVertex2f(cx, y + h);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w, y + h);
            break;
        case '3':
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y);
            // Right vertical
            glVertex2f(cx + w, y);
            glVertex2f(cx + w, y + h);
            // Middle horizontal
            glVertex2f(cx + w*0.3f, y + h/2);
            glVertex2f(cx + w, y + h/2);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w, y + h);
            break;
        case '4':
            // Left vertical (top half)
            glVertex2f(cx, y);
            glVertex2f(cx, y + h/2);
            // Right vertical
            glVertex2f(cx + w, y);
            glVertex2f(cx + w, y + h);
            // Horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w, y + h/2);
            break;
        case '5':
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y);
            // Left vertical (top half)
            glVertex2f(cx, y);
            glVertex2f(cx, y + h/2);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w, y + h/2);
            // Right vertical (bottom half)
            glVertex2f(cx + w, y + h/2);
            glVertex2f(cx + w, y + h);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w, y + h);
            break;
        case '6':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w, y + h/2);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w, y + h);
            // Right vertical (bottom half)
            glVertex2f(cx + w, y + h/2);
            glVertex2f(cx + w, y + h);
            break;
        case '7':
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y);
            // Diagonal
            glVertex2f(cx + w, y);
            glVertex2f(cx + w*0.3f, y + h);
            break;
        case '8':
            // Left vertical
            glVertex2f(cx, y);
            glVertex2f(cx, y + h);
            // Right vertical
            glVertex2f(cx + w, y);
            glVertex2f(cx + w, y + h);
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w, y + h/2);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w, y + h);
            break;
        case '9':
            // Top horizontal
            glVertex2f(cx, y);
            glVertex2f(cx + w, y);
            // Left vertical (top half)
            glVertex2f(cx, y);
            glVertex2f(cx, y + h/2);
            // Right vertical
            glVertex2f(cx + w, y);
            glVertex2f(cx + w, y + h);
            // Middle horizontal
            glVertex2f(cx, y + h/2);
            glVertex2f(cx + w, y + h/2);
            // Bottom horizontal
            glVertex2f(cx, y + h);
            glVertex2f(cx + w, y + h);
            break;
        default:
            // Unknown number - draw a simple box
            glVertex2f(cx, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.7f);
            glVertex2f(cx + w*0.6f, y + h*0.7f);
            glVertex2f(cx, y + h*0.7f);
            glVertex2f(cx, y + h*0.7f);
            glVertex2f(cx, y + h*0.3f);
            break;
    }
}

void TextRenderer::drawSymbol(char c, float cx, float y, float w, float h) {
    switch (c) {
        case ' ':
            // Space - no lines
            break;
        case '.':
            // Dot
            glVertex2f(cx + w*0.4f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h);
            glVertex2f(cx + w*0.6f, y + h);
            glVertex2f(cx + w*0.4f, y + h);
            glVertex2f(cx + w*0.4f, y + h);
            glVertex2f(cx + w*0.4f, y + h*0.8f);
            break;
        case ':':
            // Colon - two dots
            glVertex2f(cx + w*0.4f, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.4f);
            glVertex2f(cx + w*0.6f, y + h*0.4f);
            glVertex2f(cx + w*0.4f, y + h*0.4f);
            glVertex2f(cx + w*0.4f, y + h*0.4f);
            glVertex2f(cx + w*0.4f, y + h*0.3f);
            // Second dot
            glVertex2f(cx + w*0.4f, y + h*0.6f);
            glVertex2f(cx + w*0.6f, y + h*0.6f);
            glVertex2f(cx + w*0.6f, y + h*0.6f);
            glVertex2f(cx + w*0.6f, y + h*0.7f);
            glVertex2f(cx + w*0.6f, y + h*0.7f);
            glVertex2f(cx + w*0.4f, y + h*0.7f);
            glVertex2f(cx + w*0.4f, y + h*0.7f);
            glVertex2f(cx + w*0.4f, y + h*0.6f);
            break;
        case '-':
            // Dash/Hyphen
            glVertex2f(cx + w*0.2f, y + h/2);
            glVertex2f(cx + w*0.8f, y + h/2);
            break;
        case '!':
            // Exclamation
            glVertex2f(cx + w/2, y);
            glVertex2f(cx + w/2, y + h*0.7f);
            // Dot
            glVertex2f(cx + w*0.4f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h);
            glVertex2f(cx + w*0.6f, y + h);
            glVertex2f(cx + w*0.4f, y + h);
            glVertex2f(cx + w*0.4f, y + h);
            glVertex2f(cx + w*0.4f, y + h*0.8f);
            break;
        case '?':
            // Question mark
            glVertex2f(cx, y);
            glVertex2f(cx + w*0.8f, y);
            glVertex2f(cx + w*0.8f, y);
            glVertex2f(cx + w*0.8f, y + h*0.4f);
            glVertex2f(cx + w*0.8f, y + h*0.4f);
            glVertex2f(cx + w/2, y + h*0.4f);
            glVertex2f(cx + w/2, y + h*0.4f);
            glVertex2f(cx + w/2, y + h*0.7f);
            // Dot
            glVertex2f(cx + w*0.4f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h);
            glVertex2f(cx + w*0.6f, y + h);
            glVertex2f(cx + w*0.4f, y + h);
            glVertex2f(cx + w*0.4f, y + h);
            glVertex2f(cx + w*0.4f, y + h*0.8f);
            break;
        case ',':
            // Comma
            glVertex2f(cx + w*0.4f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h);
            glVertex2f(cx + w*0.6f, y + h);
            glVertex2f(cx + w*0.4f, y + h);
            glVertex2f(cx + w*0.4f, y + h);
            glVertex2f(cx + w*0.4f, y + h*0.8f);
            // Tail
            glVertex2f(cx + w*0.4f, y + h);
            glVertex2f(cx + w*0.3f, y + h*1.1f);
            break;
        case '(':
            // Left parenthesis
            glVertex2f(cx + w*0.6f, y);
            glVertex2f(cx + w*0.3f, y + h*0.2f);
            glVertex2f(cx + w*0.3f, y + h*0.2f);
            glVertex2f(cx + w*0.3f, y + h*0.8f);
            glVertex2f(cx + w*0.3f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h);
            break;
        case ')':
            // Right parenthesis
            glVertex2f(cx + w*0.3f, y);
            glVertex2f(cx + w*0.6f, y + h*0.2f);
            glVertex2f(cx + w*0.6f, y + h*0.2f);
            glVertex2f(cx + w*0.6f, y + h*0.8f);
            glVertex2f(cx + w*0.6f, y + h*0.8f);
            glVertex2f(cx + w*0.3f, y + h);
            break;
        case '/':
            // Forward slash
            glVertex2f(cx, y + h);
            glVertex2f(cx + w, y);
            break;
        case '\\':
            // Backslash
            glVertex2f(cx, y);
            glVertex2f(cx + w, y + h);
            break;
        case '+':
            // Plus
            glVertex2f(cx + w/2, y + h*0.2f);
            glVertex2f(cx + w/2, y + h*0.8f);
            glVertex2f(cx + w*0.2f, y + h/2);
            glVertex2f(cx + w*0.8f, y + h/2);
            break;
        case '=':
            // Equals
            glVertex2f(cx + w*0.2f, y + h*0.4f);
            glVertex2f(cx + w*0.8f, y + h*0.4f);
            glVertex2f(cx + w*0.2f, y + h*0.6f);
            glVertex2f(cx + w*0.8f, y + h*0.6f);
            break;
        case '*':
            // Asterisk
            glVertex2f(cx + w/2, y + h*0.2f);
            glVertex2f(cx + w/2, y + h*0.8f);
            glVertex2f(cx + w*0.2f, y + h*0.3f);
            glVertex2f(cx + w*0.8f, y + h*0.7f);
            glVertex2f(cx + w*0.8f, y + h*0.3f);
            glVertex2f(cx + w*0.2f, y + h*0.7f);
            break;
        case '%':
            // Percent
            // Top circle
            glVertex2f(cx + w*0.1f, y + h*0.1f);
            glVertex2f(cx + w*0.3f, y + h*0.1f);
            glVertex2f(cx + w*0.3f, y + h*0.1f);
            glVertex2f(cx + w*0.3f, y + h*0.4f);
            glVertex2f(cx + w*0.3f, y + h*0.4f);
            glVertex2f(cx + w*0.1f, y + h*0.4f);
            glVertex2f(cx + w*0.1f, y + h*0.4f);
            glVertex2f(cx + w*0.1f, y + h*0.1f);
            // Bottom circle
            glVertex2f(cx + w*0.6f, y + h*0.6f);
            glVertex2f(cx + w*0.8f, y + h*0.6f);
            glVertex2f(cx + w*0.8f, y + h*0.6f);
            glVertex2f(cx + w*0.8f, y + h*0.9f);
            glVertex2f(cx + w*0.8f, y + h*0.9f);
            glVertex2f(cx + w*0.6f, y + h*0.9f);
            glVertex2f(cx + w*0.6f, y + h*0.9f);
            glVertex2f(cx + w*0.6f, y + h*0.6f);
            // Diagonal line
            glVertex2f(cx + w*0.2f, y + h*0.8f);
            glVertex2f(cx + w*0.7f, y + h*0.2f);
            break;
        default:
            // Unknown symbol - draw a simple box
            glVertex2f(cx, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.3f);
            glVertex2f(cx + w*0.6f, y + h*0.7f);
            glVertex2f(cx + w*0.6f, y + h*0.7f);
            glVertex2f(cx, y + h*0.7f);
            glVertex2f(cx, y + h*0.7f);
            glVertex2f(cx, y + h*0.3f);
            break;
    }
}
