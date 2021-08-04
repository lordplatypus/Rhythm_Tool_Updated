#include <SFML/Graphics.hpp>
#include "DeltaTime.h"
#include "Camera.h"
#include "Game.h"
#include "EL.h"
#include "ID.h"

int main()
{
    bool isRunning = true;//bool for main game loop
    sf::RenderWindow render_window(sf::VideoMode(960.0f, 540.0f), "Game"); //game window

    DeltaTime deltaTime;

    Camera camera(&render_window, sf::Vector2f(1920.0f, 1080.0f));
    camera.AddView(view_main); //add the main view
    camera.AddView(view_UI); //add the UI view
    camera.AddLayer(layer_main); //add the main layer
    camera.AddLayer(layer_particle); //add the particle layer
    camera.AddLayer(layer_UI); //add the UI layer

    EL EL{camera}; //Setup the Event Listener

    Game game{}; //Setup the Game

    while (EL.IsRunning())
    {//main game loop
        EL.PollEvent(render_window); //Poll Events
        game.Update(deltaTime.GetDeltaTime()); //Update phase
        render_window.clear(); //clear the render window
        camera.ClearLayers(); //clear the layers
        game.Draw(camera); //Draw phase - Gameobjects tell if and where to be drawn
        camera.DrawLayers(); //Draw phase - draw layers in order by layerID (specified in ID.h)
        render_window.display(); //display in render window
    }

    return EXIT_SUCCESS;
}