#include <SFML/Graphics.hpp>

#include "game_logic.h"
#include "window_logic.h"

float play_area_width_pixels;
float block_width_pixels;
float play_area_start_x;
float play_area_start_y;
bool is_mouse_down_left;

/* UI Elements */
sf::RectangleShape play_area(sf::Vector2f(0.0f, 0.0f));
sf::RectangleShape** play_area_rectangles;

void initialize_window(sf::RenderWindow& window)
{
  window.setFramerateLimit(MAX_FRAME_RATE);
  // window.setVerticalSyncEnabled(true);

  play_area.setFillColor(sf::Color::Black);

  // reserve memory for and instantiate the 2d array of block rectangles
  play_area_rectangles = new sf::RectangleShape*[PLAY_AREA_WIDTH_BLOCKS];
  for (int x_idx = 0; x_idx < PLAY_AREA_WIDTH_BLOCKS; x_idx++)
  {
    play_area_rectangles[x_idx] = new sf::RectangleShape[PLAY_AREA_WIDTH_BLOCKS];
    for (int y_idx = 0; y_idx < PLAY_AREA_WIDTH_BLOCKS; y_idx++)
    {
      play_area_rectangles[x_idx][y_idx] = sf::RectangleShape(sf::Vector2f(0, 0));
    }
  }

  // resize the play area and the block rectangles to fit the current window
  resize_play_area(window);
}

void cleanup_window()
{
  // delete the 2d array of block rectangles
  for (int x_idx = 0; x_idx < PLAY_AREA_WIDTH_BLOCKS; x_idx++)
  {
    delete[] play_area_rectangles[x_idx];
  }
  delete[] play_area_rectangles;
}

void initialize_controls()
{
  is_mouse_down_left = false;
}

void handle_user_input(sf::RenderWindow& window)
{
  if (is_mouse_down_left)
  {
    // get the mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // check if the mouse's position is inside the play area
    if (play_area.getGlobalBounds().contains(sf::Vector2f(mousePos)))
    {
      // convert the mouse position from pixel coordinates to block coordinates
      int block_x = (mousePos.x - play_area_start_x) / block_width_pixels;
      int block_y = (play_area_width_pixels - (mousePos.y - play_area_start_y)) / block_width_pixels;

      // convert the particle at the mouse's position to a sand particle
     set_particle(block_x, block_y, ParticleType::SAND);
    }
  }
}

void resize_play_area(sf::RenderWindow& window)
{
  // get the window's current dimensions
  const sf::Vector2u window_size = window.getSize();
  unsigned int width = window_size.x;
  unsigned int height = window_size.y;

  // calculate the dimensions of the play area
  // (the play area is a square that is centered in the window)
  if (width >= height)
  {
    play_area_width_pixels = height;
    play_area_start_x = (width - play_area_width_pixels) / 2;
    play_area_start_y = 0;
  }
  else
  {
    play_area_width_pixels = width;
    play_area_start_x = 0;
    play_area_start_y = (height - play_area_width_pixels) / 2;
  }
  block_width_pixels = play_area_width_pixels / PLAY_AREA_WIDTH_BLOCKS;
  
  // update the play area rectangle object
  play_area.setPosition({play_area_start_x, play_area_start_y});
  play_area.setSize(sf::Vector2f(play_area_width_pixels, play_area_width_pixels));

  // update the block rectangle objects
  float x, y;
  for (int x_idx = 0; x_idx < PLAY_AREA_WIDTH_BLOCKS; x_idx++)
  {
    for (int y_idx = 0; y_idx < PLAY_AREA_WIDTH_BLOCKS; y_idx++)
    {
      x = play_area_start_x + (x_idx * block_width_pixels);
      y = play_area_start_y + play_area_width_pixels - ((y_idx+1) * block_width_pixels);

      play_area_rectangles[x_idx][y_idx].setPosition({x, y});
      play_area_rectangles[x_idx][y_idx].setSize(sf::Vector2f(block_width_pixels, block_width_pixels));
    }
  }
}

void handle_drawing(sf::RenderWindow& window)
{
  // clears the window with a grey color
  window.clear(sf::Color(50, 50, 50));

  // draws the blank play area
  window.draw(play_area);

  // gets the array of particle types
 ParticleType** block_types = get_particle_grid();

  // iterates over each particle and draws it
  for (int x_idx = 0; x_idx < PLAY_AREA_WIDTH_BLOCKS; x_idx++)
  {
    for (int y_idx = 0; y_idx < PLAY_AREA_WIDTH_BLOCKS; y_idx++)
    {
      // sets the color of the particle based on its type
      switch (block_types[x_idx][y_idx])
      {
        case ParticleType::SAND:
          play_area_rectangles[x_idx][y_idx].setFillColor(sf::Color::Yellow);
        break;
        default:
          play_area_rectangles[x_idx][y_idx].setFillColor(sf::Color::Black);
        break;
      }
      window.draw(play_area_rectangles[x_idx][y_idx]);
    }
  }
}

void handle_window_event(const std::optional<sf::Event> event, sf::RenderWindow &window, bool &running)
{
  if (event->is<sf::Event::Closed>())
  {
    // ends the program
    running = false;
  }
  else if (const auto* resized = event->getIf<sf::Event::Resized>())
  {
    // Resets the view after resizing
    // (because SFML stretches on resize by default)
    const sf::Vector2f new_window_size = {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)};
    const sf::View view(sf::FloatRect({0.0f, 0.0f}, new_window_size));
    window.setView(view);
    resize_play_area(window);
  }

  // Mouse Events
  else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
  {
    switch (mouseButtonPressed->button)
    {
      case sf::Mouse::Button::Left:
        if (!is_mouse_down_left) {
          is_mouse_down_left = true;
        }
      break;
      case sf::Mouse::Button::Right:
      break;
    }
  }
  else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
  {
    switch (mouseButtonReleased->button)
    {
      case sf::Mouse::Button::Left:
        is_mouse_down_left = false;
      break;
      case sf::Mouse::Button::Right:
      break;
    }
  }

  // Keyboard Events
  else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
  {
    switch (keyPressed->scancode)
    {
      case sf::Keyboard::Scan::Escape:
        running = false;
      break;
    }
  }
}
