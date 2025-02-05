#include <SFML/Graphics.hpp>
#include <iostream>

#include "game_logic.h"
#include "ui_logic.h"
#include "window_logic.h"

bool is_mouse_down_left = false;
int brush_size = 3;

void handle_user_input(sf::RenderWindow& window)
{
  if (is_mouse_down_left)
  {
    // get the mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // check if the mouse's position is inside the play area
    sf::FloatRect play_area = get_play_area_bounds();
    if (play_area.contains(sf::Vector2f(mousePos)))
    {
      const float block_width_pixels = 
          play_area.size.x / PLAY_AREA_WIDTH_BLOCKS;
      const float block_height_pixels = 
          play_area.size.y / PLAY_AREA_WIDTH_BLOCKS;

      // Error checking
      if (brush_size < 1)
      {
        std::cerr << "Error: brush size must be at least 1" << std::endl;
        brush_size = 1;
      }
      // convert the mouse position from pixel coordinates to block coordinates
      int block_x = (mousePos.x - play_area.position.x) / block_width_pixels;
      int block_y = (play_area.size.y - (mousePos.y - play_area.position.y)) / block_height_pixels;

      for (int x_offset = -(brush_size-1); x_offset <= brush_size-1; x_offset++){
        if (block_x + x_offset < 0 || block_x + x_offset >= PLAY_AREA_WIDTH_BLOCKS){
          continue;
        }
        
        for (int y_offset = -(brush_size-1); y_offset <= brush_size-1; y_offset++)  
        {
          if (block_y + y_offset < 0 || block_y + y_offset >= PLAY_AREA_WIDTH_BLOCKS){
            continue;
          }
          convert_particle(block_x + x_offset, block_y + y_offset, ParticleType::SAND);
        }
      }
    }
  }
}

void handle_mouse_button_pressed(const sf::Event::MouseButtonPressed* mouse_button_pressed)
{
  switch (mouse_button_pressed->button)
  {
    case sf::Mouse::Button::Left:
      is_mouse_down_left = true;
    break;
    case sf::Mouse::Button::Right:
      // TODO: implement right-click functionality
    break;
  }
}

void handle_mouse_button_released(const sf::Event::MouseButtonReleased* mouse_button_released)
{
  switch (mouse_button_released->button)
  {
    case sf::Mouse::Button::Left:
      is_mouse_down_left = false;
    break;
    case sf::Mouse::Button::Right:
      // TODO: implement right-click functionality
    break;
  }
}

void handle_key_pressed(const sf::Event::KeyPressed* key_pressed, bool &running)
{
  switch (key_pressed->scancode)
    {
      
      case sf::Keyboard::Scan::Escape:
        running = false;
      break;
      default:
        
      break;
    }
}

void draw_ui(sf::RenderWindow& window)
{ 
  // TODO: implement UI drawing
}