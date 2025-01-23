#include <SFML/Graphics.hpp>

#include "game/gameLogic.h"
#include "game/windowLogic.h"
#ifdef DEBUG
#include "debug/debugFunctions.h"
#include <string>
#endif

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1080u, 720u}), "Falling Sand");
    initialize_window(window);
    initialize_controls();
    initialize_game();

#ifdef DEBUG
    initialize_debug();
    // print_window_settings(window);

    Timer physics_timer = Timer();
    Timer frame_timer = Timer();
    Timer draw_timer = Timer();
    frame_timer.start();
#endif

    // runs the main loop, upper limited in speed by the frame rate
    bool running = true;
    while (running)
    {
        while (const std::optional event = window.pollEvent())
        {
            handle_window_event(event, window, running);
        }

        // 1. handle user input
        handle_user_input(window);

#ifdef DEBUG
        physics_timer.start();
#endif
        // 2. update things based on physics
        handle_physics();

#ifdef DEBUG
        physics_timer.stop();
        std::string physics_time_str = "Physics time: " + std::to_string(physics_timer.get_elapsed_time());

        draw_timer.start();
#endif

        // 3. draw everything
        handle_drawing(window);

#ifdef DEBUG
        draw_timer.stop();
        std::string draw_time_str = "Draw time: " + std::to_string(draw_timer.get_elapsed_time());

        frame_timer.stop();
        std::string frame_time_str = "Frame time: " + std::to_string(frame_timer.get_elapsed_time());
        std::string fps_str = "FPS: " + std::to_string(1.0 / frame_timer.get_elapsed_time());

        draw_text_to_window(window, physics_time_str, 1);
        draw_text_to_window(window, frame_time_str, 2);
        draw_text_to_window(window, fps_str, 3);
        draw_text_to_window(window, draw_time_str, 4);

        frame_timer.start();
#endif

        reset_grid();
        
        // end the current frame (internally swaps the front and back buffers).
        // (Takes whatever was drawn to the current "back" buffer and displays 
        // it on the screen.)
        window.display();
    }

    cleanup_game();
    cleanup_window();

    return 0;
}
