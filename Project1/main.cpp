/*

Purpose: Learn C++ and have fun

SFML Tutorial Website: (https://www.sfml-dev.org/tutorials/2.5/)
FillColor uses Decimal Code R,G,B Color Reference: (https://www.rapidtables.com/web/color/RGB_Color.html)


To Do: 
    -user prompted but independent projectile movement
    -restrict projectile movement to the window

    =============================================================
                             Graveyard





    =============================================================

    if there are any problems w/ the debugger - copy dll back into x64 directory (C:\Users\\Documents\Visual Studio 2017\Projects\Project1\x64\Debug)


    Two different methods to color objects and etc..
    ...(sf::Color::Black);
    ...(sf::Color(0,0,0);
*/

#include <SFML/Graphics.hpp>
#include <iostream>



int main() {

    //Create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Zone Of The Square");

    //Declaring window bounds and acquiring window size
    sf::FloatRect windowBounds(sf::Vector2f(0.f, 0.f), window.getDefaultView().getSize());

    //Defining and sizing the square
    sf::RectangleShape square(sf::Vector2f(100, 100));
	square.setFillColor(sf::Color(47, 79, 79));

	sf::RectangleShape projectile(sf::Vector2f(10, 10));
	projectile.setFillColor(sf::Color(255, 0, 0));

    //Setting starting position
    square.setPosition(0, 0);
	projectile.setPosition(0, 0);

	sf::Clock clock;

    bool fire = false;

    //Run the program as long as the window is open
    while (window.isOpen()) {

        //Clear the window with a color
        window.clear(sf::Color::White);

        //Draw the rest of the fucking owl
        window.draw(square);
		//window.draw(projectile);

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

        //frame rate independent movement
        int speed = 100;
        float projectilespeed = 0.80;

        sf::Time elapsedTime = clock.restart();
        float tempSpeed = elapsedTime.asSeconds() * speed;

        //Square controls (Left-10,0) (Right10,0) (Up0,-10) (Down0,10)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            //Left arrow key is pressed: move the rectangle
            square.move(-tempSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            //Right arrow key is pressed: move the rectangle
            square.move (tempSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            //Up arrow key is pressed: move the rectangle
            square.move(0, -tempSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            //Down arrow key is pressed: move the rectangle
            square.move(0, tempSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            //Space bar is pressed: fire projectile
            fire = true;
            if (fire = true)
            {
                window.draw(projectile);
                projectile.setPosition(square.getPosition());
            }
        }

        //Getting all objects position position
        sf::Vector2f position = square.getPosition();
		sf::Vector2f position2 = projectile.getPosition();

        //Restricting object movement to the window
        position.x = std::max(position.x, windowBounds.left);
        position.x = std::min(position.x, windowBounds.left + windowBounds.width - square.getSize().x);
        position.y = std::max(position.y, windowBounds.top);
        position.y = std::min(position.y, windowBounds.top + windowBounds.height - square.getSize().y);
        square.setPosition(position);

		position2.x = std::max(position2.x, windowBounds.left);
		position2.x = std::min(position2.x, windowBounds.left + windowBounds.width - projectile.getSize().x);
		position2.y = std::max(position2.y, windowBounds.top);
		position2.y = std::min(position2.y, windowBounds.top + windowBounds.height - projectile.getSize().y);
		projectile.setPosition(position2);

		//End the current frame
		window.display();
    }
}