#include <SFML/Graphics.hpp>
#include "DeltaTime.h"
#include "Camera.h"
#include "Game.h"
#include "LP.h"

int main()
{
    bool isRunning = true;//bool for main game loop
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Game"); //game window

    DeltaTime deltaTime;
    Camera camera;
    camera.SetCameraViewSize(window.getSize().x, window.getSize().y);
    camera.SetTarget(sf::Vector2f(camera.GetCameraViewSize().x/2, camera.GetCameraViewSize().y/2));
    window.setView(*camera.GetCamera());
    Game game{&camera};

    while (isRunning)
    {//main game loop
        sf::Event event; //events
        while (window.pollEvent(event))
        {//
            if (event.type == sf::Event::Resized)
            {
                camera.SetCameraViewSize(sf::FloatRect(0, 0, event.size.width, event.size.height));
                window.setView(*camera.GetCamera());   
            }
            else if (event.type == sf::Event::Closed)
            {
                isRunning = false;
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                isRunning = false;
            }
        }
        game.Update(deltaTime.GetDeltaTime());
        window.setView(*camera.GetCamera());
        game.Draw(); //objects are added to the draw maps
        window.clear();
        LP::Draw(&window); //actually draw objects
        window.display();
    }
    return EXIT_SUCCESS;
}