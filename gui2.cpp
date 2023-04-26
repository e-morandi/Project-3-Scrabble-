#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

extern void printbest1(void);
extern void printbest2(void);
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Create an array of alphabet tiles
    const int NUM_TILES = 26;
    sf::RectangleShape tiles[NUM_TILES];
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text letters[NUM_TILES];
    std::string input;

    for (int i = 0; i < NUM_TILES; i++) {
        tiles[i].setSize(sf::Vector2f(50.0f, 50.0f));
        tiles[i].setPosition(sf::Vector2f(50.0f + i % 10 * 60.0f, 50.0f + i / 10 * 60.0f));
        tiles[i].setFillColor(sf::Color::White);
        tiles[i].setOutlineColor(sf::Color::Black);
        tiles[i].setOutlineThickness(2.0f);

        letters[i].setFont(font);
        letters[i].setCharacterSize(24);
        letters[i].setString(std::string(1, 'A' + i));
        letters[i].setPosition(sf::Vector2f(58.0f + i % 10 * 60.0f, 58.0f + i / 10 * 60.0f));
    }
    int l=0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                // Check which tile was clicked and add its letter to the input string
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (int i = 0; i < NUM_TILES; i++) {
                    if (tiles[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        input += std::string(1, 'A' + i);
                        std::cout << "Input: " << input << std::endl;
                        l++;
                        
                        break;
                    }
                }
            }
            
        }
        if(l==7){
            break;
        }

        window.clear(sf::Color::White);

        // Draw the tiles and letters
        for (int i = 0; i < NUM_TILES; i++) {
            window.draw(tiles[i]);
            window.draw(letters[i]);
        }

        window.display();
    }
    std::cout<<input;
    printbest1(input);
    printbest2(input);
    return 0;
}
