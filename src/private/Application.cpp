#include "Application.hpp"

Application::Application(): simulation(world) {
    window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE);
    window.setVerticalSyncEnabled(true);
    if (!window.isOpen()) {
        throw std::runtime_error("Failed to create render window.");
    }
}

void Application::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        handleEvents();

        float dt = clock.restart().asSeconds();
        
        simulation.update(dt);

        window.clear(Config::BACKGROUND_COLOR);
        renderer.render(window, world, simulation.getPostmen());
        window.display();
    }
}

void Application::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
