#include <iostream>
#include <fstream>
#include <sstream>
#include<unordered_map>
#include<chrono>
#include <SFML/Graphics.hpp>
#include "RedBlackTree.h"
#include "hashmap.h"

using namespace std;
using namespace std::chrono;
unordered_map<string, unordered_map<string, int>> mp; //this basically stores the sorted string mapping from sorted to original and their score 
unordered_map<char, int> point_values = {
    {'A', 1},
    {'B', 3},
    {'C', 3},
    {'D', 2},
    {'E', 1},
    {'F', 4},
    {'G', 2},
    {'H', 4},
    {'I', 1},
    {'J', 8},
    {'K', 5},
    {'L', 1},
    {'M', 3},
    {'N', 1},
    {'O', 1},
    {'P', 3},
    {'Q', 10},
    {'R', 1},
    {'S', 1},
    {'T', 1},
    {'U', 1},
    {'V', 4},
    {'W', 4},
    {'X', 8},
    {'Y', 4},
    {'Z', 10}
};
int calculate_score(string word) {
    int score = 0;
    for (char c : word) {
        score += point_values[c];
    }
    return score;
}

void readFile(std::string& filename, std::vector<std::string>& s) {
    std::ifstream file;
    file.open(filename);
    std::string data;
    while (std::getline(file, data)) {
        std::istringstream line(data);
        std::string temp;
        std::getline(line, temp);
        s.push_back(temp);
    }
}

void resultScreen(std::vector<std::string>& result, std::chrono::duration<double> d) {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Output");

    // Set up the output display
    sf::Font font;
    font.loadFromFile("arial.ttf");

    std::vector<sf::Text> textLines;
    result.push_back("time taken is " + to_string(d.count()) + "s");

    for (int i = 0; i < result.size(); i++) {
        sf::Text line(result[i], font, 14);
        line.setPosition(20.0f, 20.0f + 15.0f * i);
        line.setFillColor(sf::Color::Black);
        textLines.push_back(line);
    }

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < textLines.size(); i++) {
            window.draw(textLines[i]);
        }
        window.display();
    }
}

int main() {
    // Read in the dictionary file
    vector<string> s;
    string filename = "dictionary.txt";
    readFile(filename, s);
    rbTree tree;
    Unscrambler hashmap;
    for (int i = 0; i < s.size(); i++) {
        tree.insert(calculate_score(s.at(i)), s.at(i));
        hashmap.addWord(s.at(i));
    }
    s.clear();
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
        letters[i].setFillColor(sf::Color::Black);
        letters[i].setString(std::string(1, 'A' + i));
        letters[i].setPosition(sf::Vector2f(58.0f + i % 10 * 60.0f, 58.0f + i / 10 * 60.0f));
    }
    int l = 0;
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
        if (l == 7) {
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
    //use of red black tree, start timer and intialize containers to be used on return
    std::chrono::time_point<std::chrono::system_clock> start, end;
    vector<string> result;
    std::set<std::string> valid;
    //push back starting line of the window
    result.push_back("Data structure being used is a Red Black Tree");
    start = std::chrono::system_clock::now();
    tree.multisearch(input, result, valid);
    end = std::chrono::system_clock::now();
    //calculate time took
    std::chrono::duration<double> d = end - start;
    //close the original tile select window
    window.close();
    resultScreen(result, d);

    //clear containers before using the hash map
    valid.clear();
    //start new timers and calculate new time took
    start = std::chrono::system_clock::now();
    hashmap.unscramble(input, valid);
    end = std::chrono::system_clock::now();
    d = end - start;
    result.clear();
    result.push_back("Data structure being used is a Hash Map");
    //push all the items in the set into a vector with there scores, cuts off the words less than 6
    for (auto it = valid.begin(); it != valid.end(); it++) {
        if (calculate_score(*it) > 6) {
            result.push_back(*it + ", " + to_string(calculate_score(*it)));
        }
    }
    //pull up new screen after first one is closed
    resultScreen(result, d);
    return 0;
}
