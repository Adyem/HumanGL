#include "../includes/Application/Application.hpp"

int main() {
    try {
        Application app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Application error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown application error occurred" << std::endl;
        return 1;
    }

    return 0;
}
