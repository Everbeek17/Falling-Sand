#include <SFML/Graphics.hpp>

#include "game/game_logic.h"
#include "game/ui_logic.h"
#include "game/window_logic.h"
#ifdef DEBUG
#include "debug/debug_functions.h"
#include <string>
#endif

int main()
{
  auto window = sf::RenderWindow(sf::VideoMode({1080u, 720u}), "Falling Sand");
  initialize_window(window);
  initialize_game();

#ifdef DEBUG
  initialize_debug();
  // print_window_settings(window);

  Timer physics_timer = Timer();
  float physics_running_total = 0;
  std::string physics_time_str = "Physics time: " + std::to_string(0);

  Timer draw_timer = Timer();
  float draw_running_total = 0;
  std::string draw_time_str = "Draw time: " + std::to_string(0);

  Timer frame_timer = Timer();
  float frame_running_total = 0;
  std::string frame_time_str = "Frame time: " + std::to_string(0);

  std::string fps_str = "FPS: " + std::to_string(0);

  Timer running_avg_timer = Timer();
  int running_avg_frame_count = 0;

  running_avg_timer.start();
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
    physics_running_total += physics_timer.get_elapsed_time();

    draw_timer.start();
#endif

    // 3. draw everything
    handle_drawing(window);

#ifdef DEBUG
    draw_timer.stop();
    draw_running_total += draw_timer.get_elapsed_time();

    frame_timer.stop();
    frame_running_total += frame_timer.get_elapsed_time();

    running_avg_frame_count++;

    running_avg_timer.stop();
    if (running_avg_timer.get_elapsed_time() > DEBUG_DISPLAY_INTERVAL_DURATION)
    {
      float running_avg_physics = physics_running_total / running_avg_frame_count;
      physics_running_total = 0;
      float running_avg_draw = draw_running_total / running_avg_frame_count;
      draw_running_total = 0;
      float running_avg_frame = frame_running_total / running_avg_frame_count;
      frame_running_total = 0;

      physics_time_str = "Physics time: " + std::to_string(running_avg_physics);
      draw_time_str = "Draw time: " + std::to_string(running_avg_draw);
      frame_time_str = "Frame time: " + std::to_string(running_avg_frame);
      fps_str = "FPS: " + std::to_string(1.0 / running_avg_frame);

      running_avg_frame_count = 0;
      running_avg_timer.start();
    }
    
    draw_text_to_window(window, physics_time_str, 1);
    draw_text_to_window(window, draw_time_str, 2);
    draw_text_to_window(window, frame_time_str, 3);
    draw_text_to_window(window, fps_str, 4);
    
    frame_timer.start();
#endif

    //TODO: send a reference to the correct grid to the window logic
    // at the end of handle_physics, and then call this function within handle_
    // physics instead of out here.
    reset_grid();
    
    // end the current frame 
    // things are not drawn directly to the window, but to a hidden buffer. This buffer is then copied to the window when you call .display() -- this is called double-buffering.
    window.display();
  }

  cleanup_game();

  return 0;
}
