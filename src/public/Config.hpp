#pragma once
#include <SFML/Graphics/Color.hpp>

namespace Config {
    // Application
    constexpr const char* WINDOW_TITLE = "Postman Simulator";

    // Window
    constexpr unsigned WINDOW_WIDTH = 900;
    constexpr unsigned WINDOW_HEIGHT = 600;
    inline const sf::Color BACKGROUND_COLOR{30, 30, 30};

    // Rendering
    constexpr float CITY_RADIUS = 8.0f;
    constexpr float POSTMAN_RADIUS = 6.0f;
    constexpr float CITY_OUTLINE = 2.0f;
    constexpr float DEST_CITY_OUTLINE = 2.0f;
    constexpr float PATH_LINE_OFFSET = 1.5f;
    constexpr float PATH_LINE_SPACING = 2.0f;
    constexpr unsigned TEXT_SIZE = 14;
    constexpr float LABEL_Y_OFFSET = -25.0f;
    constexpr const char* FONT_PATH = "Arimo-Regular.ttf";

    // Simulation
    constexpr float DEFAULT_POSTMAN_SPEED = 80.0f;
    constexpr float SNAP_DISTANCE = 1.0f;
}