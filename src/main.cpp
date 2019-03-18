/*

Purpose: Learn C++ and have fun

SFML Tutorial Website: (https://www.sfml-dev.org/tutorials/2.5/)
FillColor uses Decimal Code R,G,B Color Reference: (https://www.rapidtables.com/web/color/RGB_Color.html)


        @To Do:
        gut code from ground up, replace code with known working methods
        replace "Mouse::isButtonPressed(Mouse::Left)" with spacebar [maybe use both..?]
        
        erase projectiles as they leave the window and restrict player movement to the window
        draw enemies

    =============================================================
                             Graveyard


        You only need one flag: is there a projectile?
        When the space bar is pressed and the flag is false, set the projectile's position to the square's position, and set the flag to true
        When the flag is true, move the projectile and draw it
        When the projectile is out of bounds, set the flag to false.


    =============================================================

    if there are any problems w/ the debugger - copy dll back into x64 directory (C:\Users\\Documents\Visual Studio 2017\Projects\Project1\x64\Debug)


    Two different methods to color objects and etc..
    ...(sf::Color::Black);
    ...(sf::Color(0,0,0);
*/


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace sf;

int main() {

    //Create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Zone Of The Square");

    //Frame limit
    window.setFramerateLimit(60);

    //Declaring window bounds and acquiring window size
    sf::FloatRect windowBounds(sf::Vector2f(0.f, 0.f), window.getDefaultView().getSize());

    //Defining and sizing the player and projectile
    CircleShape player;
    player.setFillColor(Color::Blue);
    player.setRadius(20);
    Vector2f playerCenter;

    CircleShape projectile;
    projectile.setFillColor(Color::Yellow);
    projectile.setRadius(5);

    //Definig and sizing the enemies
    CircleShape enemy;
    enemy.setFillColor(Color::Red);
    enemy.setRadius(25);

    //Setting starting position
    player.setPosition(window.getSize().x / 2 - player.getRadius(), window.getSize().y - player.getRadius() * 2 - 10.f);

    //Variables
    int shooting = 0;

    vector <CircleShape> projectiles;
    projectiles.push_back(CircleShape(projectile));

    vector <CircleShape> enemies;

    //Run the program as long as the window is open
    while (window.isOpen()) {

        //Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            //"Close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // defining Player Center
        playerCenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());

        if (shooting < 9) {
            shooting++;
        }

        //Input to fire a projectile
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shooting >= 9) {
            projectile.setPosition(playerCenter);
            projectiles.push_back(CircleShape(projectile));

            shooting = 0;
        }

        //Square controls (Left-10,0) (Right10,0) (Up0,-10) (Down0,10)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            //Left arrow key is pressed: move the player LEFT
            player.move(-10.f, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            //Left arrow key is pressed: move the player LEFT
            player.move(-10.f, 0);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            //Right arrow key is pressed: move the player RIGHT
            player.move(10.f, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            //Right arrow key is pressed: move the player RIGHT
            player.move(10.f, 0);
        }

        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            //Up arrow key is pressed: move the rectangle
            player.move(0, -10.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            //Down arrow key is pressed: move the rectangle
            player.move(0, 10.f);
        }*/

        for (size_t i = 0; i < projectiles.size(); i++)
        {
            projectiles[i].move(0.f, -10.f);
        }

        //End the current frame

        window.clear();
        window.draw(player);

        for (size_t i = 0; i < projectiles.size(); i++){

            window.draw(projectiles[i]);
        }

        window.display();
    }

    return 0;
}
