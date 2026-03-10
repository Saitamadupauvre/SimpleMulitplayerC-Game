#include "./core/Application.hpp"

#include <exception>
#include <iostream>

int main()
{
    try {
        Application app;

        app.run();
        return app.getExitCode();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << '\n';
        return FAILURE_STATUS;
    }

    return FAILURE_STATUS;
}
