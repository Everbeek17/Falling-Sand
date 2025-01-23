#ifdef DEBUG

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../game/window_logic.h"

// Prints some of the window's settings to the console.
void print_window_settings(const sf::Window& window) {
  sf::ContextSettings settings = window.getSettings();

  std::cout << "depth bits:" << settings.depthBits << std::endl;
  std::cout << "stencil bits:" << settings.stencilBits << std::endl;
  std::cout << "antialiasing level:" << settings.antiAliasingLevel << std::endl;
  std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;
}

sf::Font font;
void initialize_debug() {
  if (!font.openFromFile("../../assets/Roboto-Regular.ttf")) {
    std::cerr << "Could not load font file" << std::endl;
    return;
  }
}

const unsigned int CHARACTER_SIZE = 32;
void draw_text_to_window(sf::RenderWindow& window, const std::string& text, const unsigned int line_number) {
  sf::Text display_text(font, text, CHARACTER_SIZE);
  display_text.setFillColor(sf::Color::White);
  display_text.setStyle(sf::Text::Bold);
  display_text.setPosition({play_area_start_x + CHARACTER_SIZE, play_area_start_y + (CHARACTER_SIZE * line_number-1)});

  window.draw(display_text);
}

#endif