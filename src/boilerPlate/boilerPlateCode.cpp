#include <SFML/Graphics.hpp>

#include "../gameLogic/gameLogic.h"

void setupWindow(sf::RenderWindow& window)
{
  // sets the max framerate to 60fps
  window.setFramerateLimit(60);
  // window.setVerticalSyncEnabled(true);

  // OpenGL function calls only affect whichever window is currenlty active
  window.setActive(true);
}








void handleEvent(sf::Event event, sf::RenderWindow &window, bool &running)
{
  static bool mouseDownLeft = false;
  if (event.type == sf::Event::Closed)
  {
    // ends the program
    running = false;
  }
  else if (event.type == sf::Event::MouseButtonPressed)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      if (!mouseDownLeft) {
        mousePressedLeft();
        mouseDownLeft = true;
      }
    }
  }
  else if (event.type == sf::Event::MouseButtonReleased)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      mouseReleasedLeft();
      mouseDownLeft = false;
    }
  }

  // else if (event.type == sf::Event::Resized)
  // {
  //   // adjust the viewport when the window is resized
  //   glViewport(0, 0, event.size.width, event.size.height);
  //   std::cout << "Resized to: " << event.size.width << "x" << event.size.height << std::endl;
  // }
}