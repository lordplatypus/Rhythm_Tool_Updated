#include <SFML/Graphics.hpp>
#include "DeltaTime.h"
#include "Camera.h"
#include "Game.h"
#include "EL.h"

int main()
{
    bool isRunning = true;//bool for main game loop
    sf::RenderWindow render_window(sf::VideoMode(960.0f, 540.0f), "Game"); //game window

    DeltaTime deltaTime;

    Camera camera(&render_window, sf::Vector2f(960.0f, 540.0f));

    EL EL{camera};

    Game game{};

    while (EL.IsRunning())
    {//main game loop
        EL.PollEvent(render_window);
        game.Update(deltaTime.GetDeltaTime());
        render_window.clear();
        game.Draw(camera);
        render_window.display();
    }

    return EXIT_SUCCESS;
}