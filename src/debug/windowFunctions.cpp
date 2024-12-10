#include <SFML/Graphics.hpp>
#include <iostream>

// Prints some of the window's settings to the console.
void printWindowSettings(const sf::Window& window) {
  sf::ContextSettings settings = window.getSettings();

  std::cout << "depth bits:" << settings.depthBits << std::endl;
  std::cout << "stencil bits:" << settings.stencilBits << std::endl;
  std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
  std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;
}