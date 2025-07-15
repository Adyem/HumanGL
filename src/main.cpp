#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

struct Point {
    float x;
    float y;
};

// Helper for drawing a line between two Points
void drawLine(SDL_Renderer* renderer, const Point& a, const Point& b) {
    SDL_RenderDrawLine(renderer, static_cast<int>(a.x), static_cast<int>(a.y),
                       static_cast<int>(b.x), static_cast<int>(b.y));
}

int main(int argc, char* argv[]) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    bool running = true;
    SDL_Event event;
    float time = 0.0f; // Used for simple animation
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Update time for animation
        time += 0.016f; // ~60 FPS step

        // Basic parameters for the stick figure
        Point hip{400.0f, 400.0f};
        float bodyLength = 80.0f;
        float limbLength = 60.0f;

        // Oscillate limbs using sine wave
        float legSwing = std::sin(time) * 0.5f;   // radians
        float armSwing = std::sin(time + M_PI) * 0.5f;

        // Torso and head
        Point shoulder{hip.x, hip.y - bodyLength};
        Point head{shoulder.x, shoulder.y - 20.0f};

        // Legs
        Point leftFoot{hip.x - limbLength * std::sin(legSwing),
                       hip.y + limbLength * std::cos(legSwing)};
        Point rightFoot{hip.x + limbLength * std::sin(legSwing),
                        hip.y + limbLength * std::cos(legSwing)};

        // Arms
        Point leftHand{shoulder.x - limbLength * std::sin(armSwing),
                       shoulder.y + limbLength * std::cos(armSwing)};
        Point rightHand{shoulder.x + limbLength * std::sin(armSwing),
                        shoulder.y + limbLength * std::cos(armSwing)};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // Torso and head line
        drawLine(renderer, hip, shoulder);
        drawLine(renderer, shoulder, head);

        // Legs
        drawLine(renderer, hip, leftFoot);
        drawLine(renderer, hip, rightFoot);

        // Arms
        drawLine(renderer, shoulder, leftHand);
        drawLine(renderer, shoulder, rightHand);

        // Present
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
