#include <SFML/Graphics.hpp>

#include "game_logic.h"
#include "ui_logic.h"
#include "window_logic.h"

void draw_particles(sf::RenderWindow& window);

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

sf::FloatRect get_play_area_bounds()
{
  return block_map.get_bounding_box();
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

  draw_particles(window);

  draw_ui(window);
}

void draw_particles(sf::RenderWindow& window)
{
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
  else if (const auto* mouse_button_pressed = event->getIf<sf::Event::MouseButtonPressed>())
  {
    handle_mouse_button_pressed(mouse_button_pressed);
  }
  else if (const auto* mouse_button_released = event->getIf<sf::Event::MouseButtonReleased>())
  {
    handle_mouse_button_released(mouse_button_released);
  }

  /* Keyboard Events */
  else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>())
  {
    handle_key_pressed(key_pressed, running);
  }
}
