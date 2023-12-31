#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>


int main(int argc, char * argv[])
{
    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
    window.setFramerateLimit(60);

    float radius = 10.0f;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(68, 31, 172));
    circle.setPosition(300.0f, 300.0f);
    float circleMoveSpeedX = 3.0f;
    float circleMoveSpeedY = 1.0f;

    float RectW = 175.0f;
    float RectH = 8.0f;
    sf::RectangleShape bar(sf::Vector2f(RectW, RectH));
    bar.setPosition((float)((wWidth - RectW)/2.0), wHeight - RectH);

    sf::Font myFont;

    if (!myFont.loadFromFile("fonts/JetBrainsMonoNL-ExtraBold.ttf"))
    {
        std::cerr << "Could not load the font!\n";
        exit(-1);
    }

    sf::Text text("SFML GAME", myFont, 30);
    std::cout << text.getCharacterSize() << "\n";
    text.setPosition(0, 0);

    
    while (window.isOpen())
    {
        float barX = bar.getPosition().x;

        float XPos = circle.getPosition().x;
        float YPos = circle.getPosition().y;

        bool hitBar = ((YPos + 2*radius >= wHeight - RectH) && (XPos + 2*radius >= barX) && (XPos <= barX + RectW));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "Window Closed\n";
                window.close();
                
            }

            if (YPos >= wHeight)
            {
                std::cout << "You Lost!\n";
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                std::cout << "Key Pressed with code = " << event.key.code << "\n";

                if (event.key.code == sf::Keyboard::Up)
                {
                    std::cout << "Speed Doubled\n\n";
                    circleMoveSpeedX *= 2.0f;
                    circleMoveSpeedY *= 2.0f;

                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    std::cout << "Speed Halved\n\n";
                    circleMoveSpeedX *= 0.5f;
                    circleMoveSpeedY *= 0.5f;

                }

                if (event.key.code == sf::Keyboard::Left)
                    barX -= 20.0f;

                if (event.key.code == sf::Keyboard::Right)
                    barX += 20.0f;

            }
        }

        
        if ((XPos <= 0) || (XPos + 2*radius >= wWidth))
            circleMoveSpeedX *= -1.0f;
        if ((YPos <= 0) || hitBar)
            circleMoveSpeedY *= -1.0f;


        XPos += circleMoveSpeedX;
        YPos += circleMoveSpeedY;

        circle.setPosition(XPos, YPos);
        bar.setPosition(barX, bar.getPosition().y);

        window.clear();
        window.draw(circle);
        window.draw(text);
        window.draw(bar);
        window.display();
    }
    return 0;
}