#include <SFML/Graphics.hpp>

#include "game_logic.h"
#include "window_logic.h"

bool is_mouse_down_left = false;
BlockMap block_map({PLAY_AREA_WIDTH_BLOCKS, PLAY_AREA_WIDTH_BLOCKS});

void initialize_window(sf::RenderWindow& window)
{
  // WARNING: can either set max frame rate or vertical sync, not both
  if (USE_VSYNC)
  {
    window.setVerticalSyncEnabled(true);
  }
  else
  {
    window.setFramerateLimit(MAX_FRAME_RATE);
  }

  // resize the play area to fit the current window
  resize_play_area(window);
}

void handle_user_input(sf::RenderWindow& window)
{
  if (is_mouse_down_left)
  {
    // get the mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // check if the mouse's position is inside the play area
    sf::FloatRect play_area = block_map.get_bounding_box();
    if (play_area.contains(sf::Vector2f(mousePos)))
    {
      float block_width_pixels = play_area.size.x / PLAY_AREA_WIDTH_BLOCKS;
      float block_height_pixels = play_area.size.y / PLAY_AREA_WIDTH_BLOCKS;
      // convert the mouse position from pixel coordinates to block coordinates
      int block_x = (mousePos.x - play_area.position.x) / block_width_pixels;
      int block_y = (play_area.size.y - (mousePos.y - play_area.position.y)) / block_height_pixels;

      // convert the particle at the mouse's position to a sand particle
     convert_particle(block_x, block_y, ParticleType::SAND);
    }
  }
}

// (currently the play area is set as a window-centered square)
void resize_play_area(sf::RenderWindow& window)
{
  // get the window's current dimensions
  const sf::Vector2u window_size = window.getSize();
  unsigned int window_width = window_size.x;
  unsigned int window_height = window_size.y;

  sf::Vector2f play_area_size;
  sf::Vector2f play_area_position;

  play_area_size.x = std::min(window_width, window_height);
  play_area_size.y = play_area_size.x;

  play_area_position.x = 
      std::max(0.0f, (window_width - play_area_size.x) / 2.0f);
  play_area_position.y = 
      std::max(0.0f, (window_height - play_area_size.y) / 2.0f);

  // update the block map object
  block_map.resize(play_area_size);
  block_map.setPosition(play_area_position);
}

void handle_drawing(sf::RenderWindow& window)
{
  // clears the window to the background color
  window.clear(BACKGROUND_COLOR);

  // gets the array of particle types
  ParticleType** block_types = get_particle_grid();

  // resets all blocks in the map to the default color
  block_map.set_all_block_colors(DEFAULT_BLOCK_COLOR);

  // iterates over each particle and updates its color in BlockMap accordingly
  for (unsigned int x_idx = 0; x_idx < PLAY_AREA_WIDTH_BLOCKS; x_idx++)
  {
    for (unsigned int y_idx = 0; y_idx < PLAY_AREA_WIDTH_BLOCKS; y_idx++)
    {
      switch (block_types[x_idx][y_idx])
      {
        case ParticleType::SAND:
          block_map.set_block_color({x_idx, y_idx}, SAND_COLOR);
        break;
        default:
          // block_map.set_block_color({x_idx, y_idx}, DEFAULT_BLOCK_COLOR);
        break;
      }
    }
  }
  // Draws the BlockMap
  window.draw(block_map);
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

  /* Mouse Events */
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

  /* Keyboard Events */
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
