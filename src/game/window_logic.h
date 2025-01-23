#ifndef WINDOW_LOGIC_H
#define WINDOW_LOGIC_H

#include <SFML/Graphics.hpp>

/* Constants */
const unsigned int PLAY_AREA_WIDTH_BLOCKS = 50;
const unsigned int MAX_FRAME_RATE = 60;


/* Global Variables */
extern float play_area_width_pixels;
extern float block_width_pixels;
extern float play_area_start_x;
extern float play_area_start_y;

extern bool is_mouse_down_left;


void initialize_window(sf::RenderWindow& window);
void initialize_controls();
void cleanup_window();
void resize_play_area(sf::RenderWindow& window);
void handle_window_event(const std::optional<sf::Event> event, sf::RenderWindow &window, bool &running);
void handle_user_input(sf::RenderWindow& window);
void handle_drawing(sf::RenderWindow& window);

#endif