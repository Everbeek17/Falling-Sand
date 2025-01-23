#ifdef DEBUG

#ifndef DEBUG_FUNCTIONS_H
#define DEBUG_FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <chrono>

class Timer {
public:
	Timer();
	void start();
	void stop();
	double get_elapsed_time() const;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
	std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};

void initialize_debug();
void print_window_settings(const sf::Window& window);
void draw_text_to_window(sf::RenderWindow& window, const std::string& text, const unsigned int line_number);

#endif

#endif