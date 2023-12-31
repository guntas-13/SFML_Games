#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>


/*
    Created own Class "MyCircle" and "MyRectangle"
    that are inherited from their Super Classes 
    "sf::CircleShape" and "sf::RectangleShape" respt.
    
    The objects has their own special attributes ->
    Sx (X Speed), Sy (Y Speed), Text.
*/

class MyCircle : public sf::CircleShape
{   

    float m_sX, m_sY;
    sf::Text cText;

public:
    MyCircle(float X, float Y, float SX, float SY, float Radius, int R, int G, int B, std::string& text, sf::Font& fontLoc, int fontSize, int fR, int fG, int fB)
        : CircleShape(Radius)
        , m_sX(SX)
        , m_sY(SY)
        {   
            setPosition(X, Y);
            setFillColor(sf::Color(R, G, B));
            cText.setFont(fontLoc);
            cText.setString(text);
            cText.setCharacterSize(fontSize);
            cText.setFillColor(sf::Color(fR, fG, fB));
            cText.setPosition(X + R - cText.getLocalBounds().width/2.0, Y + R - (float)cText.getCharacterSize()/2.0);
        }
    
    void collisionUpdate(int wWidth, int wHeight)
    {
        float X = getPosition().x, Y = getPosition().y, R = getRadius();
        X += m_sX;
        Y += m_sY;

        if ((X <= 0) || (X + 2*R >= wWidth))
            m_sX *= -1.0f;
        if ((Y <= 0) || (Y + 2*R >= wHeight))
            m_sY *= -1.0f;
        
        setPosition(X, Y);
        cText.setPosition(X + R - cText.getLocalBounds().width/2.0, Y + R - (float)cText.getCharacterSize()/2.0);
    }

    sf::Text& getText()
    {
        return cText;
    }

};

class MyRectangle : public sf::RectangleShape
{   
    float m_sX, m_sY, m_W, m_H;
    sf::Text rText;

public:
    MyRectangle(float X, float Y, float SX, float SY, float W, float H, int R, int G, int B, std::string& text, sf::Font& fontLoc, int fontSize, int fR, int fG, int fB)
        : RectangleShape(sf::Vector2f(W, H))
        , m_sX(SX)
        , m_sY(SY)
        {   
            setPosition(X, Y);
            setFillColor(sf::Color(R, G, B));
            rText.setFont(fontLoc);
            rText.setString(text);
            rText.setCharacterSize(fontSize);
            rText.setFillColor(sf::Color(fR, fG, fB));
            rText.setPosition(X + W/2.0 - (rText.getLocalBounds().width)/2.0, Y + H/2.0 - (float)(rText.getCharacterSize())/2.0);
        }
    
    void collisionUpdate(int wWidth, int wHeight)
    {
        float X = getPosition().x, Y = getPosition().y, W = getSize().x, H = getSize().y;

        X += m_sX;
        Y += m_sY;

        if ((X <= 0) || (X + W >= wWidth))
            m_sX *= -1.0f;
        if ((Y <= 0) || (Y + H >= wHeight))
            m_sY *= -1.0f;
        
        setPosition(X, Y);
        rText.setPosition(X + W/2.0 - (rText.getLocalBounds().width)/2.0, Y + H/2.0 - (float)(rText.getCharacterSize())/2.0);
    }

    sf::Text& getText()
    {
        return rText;
    }

};

int main(int argc, char * argv[])
{

    std::ifstream fin("config.txt");

    if (!fin.is_open())
    {
        std::cerr << "Could not open the file!\n";
        exit(-1);
    }

    std::string winName, Font, fontFile;
    int wWidth, wHeight, fSize, fR, fG, fB;

    fin >> winName >> wWidth >> wHeight >> Font >> fontFile >> fSize >> fR >> fG >> fB;

    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Game 1");
    window.setFramerateLimit(60);

    sf::Font myFont;
    if (!myFont.loadFromFile(fontFile))
    {
        std::cerr << "Could not load the font!\n";
        exit(-1);
    }


    std::vector<MyCircle> cls;
    std::vector<MyRectangle> rects;

    // std::vector<std::shared_ptr<sf::CircleShape>> cls;
    // std::vector<std::shared_ptr<sf::RectangleShape>> rects;


    std::string shapeName;
    while(fin >> shapeName)
    {   
        std::string shapeText;
        float X, Y, SX, SY;
        int R, G, B;
        if (shapeName == "Circle")
        {
            float radius;
            fin >> shapeText >> X >> Y >> SX >> SY >> R >> G >> B >> radius;
            cls.push_back(MyCircle(X, Y, SX, SY, radius, R, G, B, shapeText, myFont, fSize, fR, fG, fB));
        }

        if (shapeName == "Rectangle")
        {
            float W, H;
            fin >> shapeText >> X >> Y >> SX >> SY >> R >> G >> B >> W >> H;
            rects.push_back(MyRectangle(X, Y, SX, SY, W, H, R, G, B, shapeText, myFont, fSize, fR, fG, fB));
        }
    }
    
    while (window.isOpen())
    {
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
            }
        }

        window.clear();

        for (auto& circle : cls)
        {
            circle.collisionUpdate(wWidth, wHeight);
            window.draw(circle);
            window.draw(circle.getText());
        }

        for (auto& rectangle : rects)
        {
            rectangle.collisionUpdate(wWidth, wHeight);
            window.draw(rectangle);
            window.draw(rectangle.getText());
        }

        window.display();
    }
    return 0;
}