#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#include "gameLogic/gameLogic.h"
#include "boilerPlate/boilerPlateCode.h"
#include "debug/DebugFunctions.h"

int main()
{
    auto window = sf::RenderWindow({1080u, 720u}, "Falling Sand");
    setupWindow(window);
    initializeGameLogic(window);

    // run the main loop
    // The program already limits the amount of times this loop fires
    // to 60 times per second. 
    // (This is done by calling window.setFramerateLimit(60))
    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            handleEvent(event, window, running);
        }
        // clear the window with a blue color
        window.clear(sf::Color::Black);

        // ticks the game by one frame
        gametick(running);


        // end the current frame (internally swaps the front and back buffers).
        // (Takes whatever was drawn to the current "back" buffer and displays 
        //  it on the screen.)
        window.display();
    }

    // release resources...

    return 0;
}
