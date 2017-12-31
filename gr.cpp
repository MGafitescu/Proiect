#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "QuizzGame");
    sf::CircleShape triangle(80, 3);
    triangle.setPosition(200, 200);
    // define a square
    sf::CircleShape square(80, 4);
    square.setPosition(10, 10);
    // define an octagon
    sf::CircleShape octagon(80, 8);
    octagon.setPosition(300, 400);

    sf::Texture texture;
if (!texture.loadFromFile("texture.jpg"))
{
    printf("Eroare");
}

sf::Sprite sprite;
sprite.setTexture(texture);
//sprite.setColor(sf::Color(255, 255, 255, 128)); 
texture.setRepeated(true);
texture.setSmooth(true);


    sf::Texture texture1;
if (!texture1.loadFromFile("image.jpg"))
{
    printf("Eroare");
}

sf::Sprite sprite1;
sprite1.setTexture(texture1);
//sprite.setColor(sf::Color(255, 255, 255, 128)); 
texture1.setRepeated(true);
texture1.setSmooth(true);
sprite1.setPosition(300,20);
sprite1.setScale(1,0.2);

// Declare and load a font
sf::Font font;
font.loadFromFile("arial.ttf");
// Create a text
sf::Text text("QuizzGame", font);
text.setCharacterSize(40);
//text.setStyle(sf::Text::Bold);
text.setColor(sf::Color::Black);
text.setPosition(300,20);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.draw(sprite1);
        window.draw(text);
        //window.draw(octagon);
        //window.draw(triangle);
        //window.draw(square);
        window.display();
    }

    return 0;
}