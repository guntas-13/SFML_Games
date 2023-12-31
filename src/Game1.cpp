#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>


int main(int argc, char * argv[])
{
    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
    window.setFramerateLimit(60);

    float radius = 50.0f;
    float initXc = 100.0f, initYc = 100.0f;

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(68, 31, 172));
    circle.setPosition(initXc, initYc);

    float circleMoveSpeedX = 3.0f, circleMoveSpeedY = 1.0f;
    float rectMoveSpeedX = -2.0f, rectMoveSpeedY = -2.0f;

    float rectW = 100.0f, rectH = 100.0f;
    float initXr = 25.0f, initYr = 100.0f;
    sf::RectangleShape rect(sf::Vector2f(rectW, rectH));
    rect.setFillColor(sf::Color(220, 20, 140));
    rect.setPosition(initXr, initYr);

    sf::Font myFont;

    if (!myFont.loadFromFile("fonts/JetBrainsMonoNL-ExtraBold.ttf"))
    {
        std::cerr << "Could not load the font!\n";
        exit(-1);
    }

    sf::Text text("SFML GAME", myFont, 30);
    std::cout << text.getCharacterSize() << "\n";
    text.setPosition(0, 0);

    sf::Text cText("CPurple", myFont, 18);
    cText.setPosition(initXc + radius - (cText.getLocalBounds().width)/2.0, initYc + radius - (float)(cText.getCharacterSize())/2.0);
    // std::cout << cText.getLocalBounds().width << "\n";
    // std::cout << cText.getCharacterSize() << "\n";

    sf::Text rText("CPink", myFont, 18);
    rText.setPosition(initXr + rectW - (rText.getLocalBounds().width)/2.0, initYr + rectH - (float)(rText.getCharacterSize())/2.0);

    
    while (window.isOpen())
    {


        float XPosc = circle.getPosition().x, YPosc = circle.getPosition().y;
        float XPosr = rect.getPosition().x, YPosr = rect.getPosition().y;


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "Window Closed\n";
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
                    rectMoveSpeedX *= 2.0f;
                    rectMoveSpeedY *= 2.0f;

                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    std::cout << "Speed Halved\n\n";
                    circleMoveSpeedX *= 0.5f;
                    circleMoveSpeedY *= 0.5f;
                    rectMoveSpeedX *= 0.5f;
                    rectMoveSpeedY *= 0.5f;

                }

            }
        }

        
        if ((XPosc <= 0) || (XPosc + 2*radius >= wWidth))
            circleMoveSpeedX *= -1.0f;
        if ((YPosc <= 0) || (YPosc + 2*radius >= wHeight))
            circleMoveSpeedY *= -1.0f;

        if ((XPosr <= 0) || (XPosr + rectW >= wWidth))
            rectMoveSpeedX *= -1.0f;
        if ((YPosr <= 0) || (YPosr + rectH >= wHeight))
            rectMoveSpeedY *= -1.0f;


        XPosc += circleMoveSpeedX;
        YPosc += circleMoveSpeedY;

        XPosr += rectMoveSpeedX;
        YPosr += rectMoveSpeedY;

        circle.setPosition(XPosc, YPosc);
        rect.setPosition(XPosr, YPosr);

        cText.setPosition(XPosc + radius - cText.getLocalBounds().width/2.0, YPosc + radius - (float)cText.getCharacterSize()/2.0);
        rText.setPosition(XPosr + rectW/2.0 - (rText.getLocalBounds().width)/2.0, YPosr + rectH/2.0 - (float)(rText.getCharacterSize())/2.0);

        window.clear();
        window.draw(circle);
        window.draw(rect);
        window.draw(text);
        window.draw(cText);
        window.draw(rText);
        window.display();
    }
    return 0;
}