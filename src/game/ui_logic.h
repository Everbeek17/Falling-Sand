#ifndef UI_LOGIC_H
#define UI_LOGIC_H

#include <SFML/Graphics.hpp>

void handle_user_input(sf::RenderWindow& window);
void handle_mouse_button_pressed(const sf::Event::MouseButtonPressed* mouse_button_pressed);
void handle_mouse_button_released(const sf::Event::MouseButtonReleased* mouse_button_released);
void handle_key_pressed(const sf::Event::KeyPressed* key_pressed, bool &running);
void draw_ui(sf::RenderWindow& window);

#endif