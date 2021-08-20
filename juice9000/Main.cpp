// Warning	C26812	The enum type 'sf::PrimitiveType' is unscoped.Prefer 'enum class' over 'enum' (Enum.3).juice9000
#pragma warning(disable: 26812)

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include "mrav.h"
#include "food.h"
#include "config.h"
#include <ios>
#include <string> 
#include <sstream>
#include "world.h"

// crtanje mrava i hrane
template<typename T>
void draw(std::vector<T>& shapes, sf::RenderWindow& window) {
    for (auto &s : shapes) {
        window.draw(s.getSprite());
    }
}
// crtanje feromona + decrement feromona svakih 1 frame
void drawMarkersFunc(sf::RenderWindow& window) {
    // radi se slika pixela kako bi samo jednom pozvali .draw()
    sf::Image tockice;
    tockice.create(Config::width, Config::height, sf::Color::Transparent);
    
    for (int i = 0; i < Config::width; ++i) {
        for (int j = 0; j < Config::height; ++j) {
            if (World::homeMatrix[i][j] > 0) {
                tockice.setPixel(i, j, sf::Color(255,255,255,120));
                World::decHome(sf::Vector2i(i,j));
                if (World::homeMatrix[i][j] < 0) World::homeMatrix[i][j] = 0;
            }
                
            if (World::foodMatrix[i][j] > 0) {
                tockice.setPixel(i, j, sf::Color::Black);
                World::decFood(sf::Vector2i(i, j));
                if (World::foodMatrix[i][j] < 0) World::foodMatrix[i][j] = 0;
            }
        }
    }
    sf::Texture texture;
    texture.loadFromImage(tockice);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    window.draw(sprite);
}


int main()
{
    // counter hrane
    int pojeli = 0;
    // brzi cout
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // renderiranje ekrana
    sf::RenderWindow window(sf::VideoMode(Config::width, Config::height), "Mravi9000");
    window.setFramerateLimit(144);
    // load textures/slike
    Config::loadTextures();
    // vektor mrava i hrane
    std::vector<Mrav> mravi;
    std::vector<Food> hrana;
    // broj mrava
    int n = Config::nMrav;
    //mravinjak
    sf::CircleShape sMravinjak(Config::rad_mravinjak);
    sMravinjak.setOrigin(Config::rad_mravinjak, Config::rad_mravinjak);
    sMravinjak.setFillColor(Config::cMravinjak);
    sMravinjak.setPosition(Config::width /2, Config::height /2);
    // text na mravinjaku sa brojem hrane
    sf::Font font;
    if (!font.loadFromFile("C:\\WINDOWS\\FONTS\\ARIAL.TTF"))
        std::cout << "can't load font" << std::endl;
    sf::Text text("FARO", font);
    text.setCharacterSize(20);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(Config::width/2, Config::height/2);
    // spremanje objekata mrava u vektor
    for (int i = 0; i < n; ++i) {
        mravi.emplace_back(i);
    }
    // delta time
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;
        World::homeMatrix[(int)Config::width / 2][(int)Config::height / 2] = 10000;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                // esc za izlaz
                if (event.key.code == sf::Keyboard::Escape) window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Right){
                    // desni klik za hranu
                    sf::Vector2f mousePosition((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
                    hrana.emplace_back(mousePosition);
                }
                break;
            }
        }

        //clear windowa
        window.clear(sf::Color(49, 99, 0));
        
        // moving
        for (int i = 0; i < n; ++i) {
            mravi[i].move(dt, window, hrana, mravi, pojeli);
        }
        // brisanje hrane koja se pojela
        auto it = std::remove_if(hrana.begin(), hrana.end(), [](const auto& x) {return x.isGone(); });
        if (it != hrana.end()) hrana.erase(it);
        // crtanje mrava, hrane i feromona
        drawMarkersFunc(window);
        draw(hrana, window);
        draw(mravi, window);
        
        //display mravinjaka i countera
        window.draw(sMravinjak);
        std::stringstream ss;
        ss << pojeli;
        text.setString(ss.str());
        ss.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}