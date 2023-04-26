#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include<unordered_map>
#include<queue>
#include<set>
#include<chrono>
#include<map>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace std::chrono;
unordered_map<string,unordered_map<string,int>> mp; //this basically stores the sorted string mapping from sorted to original and their score 
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
struct Node{
    string str;
    int score;
    Node(string str,int score){
        this->str=str;
        this->score=score;
    }
};
int calculate_score(string word) {
    int score = 0;
    for (char c : word) {
        score += point_values[c];
    }
    return score;
}
void merge(string& s, int left, int mid, int right) {
    string temp;
    int i = left;
    int j = mid + 1;
    while (i <= mid && j <= right) {
        if (s[i] < s[j]) {
            temp.push_back(s[i++]);
        } else {
            temp.push_back(s[j++]);
        }
    }
    while (i <= mid) {
        temp.push_back(s[i++]);
    }
    while (j <= right) {
        temp.push_back(s[j++]);
    }
    for (int k = left; k <= right; k++) {
        s[k] = temp[k - left];
    }
}

void mergesort(string& s, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort(s, left, mid);
        mergesort(s, mid + 1, right);
        merge(s, left, mid, right);
    }
}
void findUniqueSubsequences(string str, int index, string subseq, set<string>& uniqueSubsequences) {
    if (index == str.size()) {
        uniqueSubsequences.insert(subseq);
        return;
    }

    // Include the current character in the subsequence
    findUniqueSubsequences(str, index+1, subseq+str[index], uniqueSubsequences);

    // Exclude the current character from the subsequence
    findUniqueSubsequences(str, index+1, subseq, uniqueSubsequences);
}
struct o{
    string s;
    int score;
    o(string s,int score){
        this->s=s;
        this->score=score;
    }
};
class comparator_class{
    public:
        bool operator()(o o1, o o2){
            if(o1.score<o2.score){
                return true;
            }
            return false;
        }
};
void printbest1(string s){
    // string temp=s;
    // mergesort(temp,0,temp.length()-1);
    // int l=s.length();
    auto start = high_resolution_clock::now();
    priority_queue<o,vector<o>,comparator_class> pq;
    // for(int i=0;i<l;i++){
    //     // string t="";
    //     // for(int j=0;j<=i;j++){
    //     //     t+=temp[j];
    //     // }
    //     // // cout<<"t is "<<t<<"\n";

    //     // // now we need to find all the subsequences of this word and find them
    //     // //whether they exist in our map or not
    //     if(mp.find(t)!=mp.end()){
    //         //put in priority queue
    //         // cout<<"inserting in pq"<<"\n";
    //         for(auto it=mp[t].begin();it!=mp[t].end();it++){
    //             pq.push({it->first,it->second});
    //         }
    //         // for(auto it:mp[temp].begin();it!=mp[temp].end();it++){
    //         //     cout<<it->first<<" "<<it->second<<"\n";
    //         // }
    //     }
    // }
    set<string> uniqueSubsequences;

    findUniqueSubsequences(s, 0, "", uniqueSubsequences);

    for(string t:uniqueSubsequences){
        
        if(mp.find(t)!=mp.end()){
    //         //put in priority queue
            // cout<<"inserting in pq"<<"\n";
            for(auto it=mp[t].begin();it!=mp[t].end();it++){
                pq.push({it->first,it->second});
            }
            // for(auto it:mp[temp].begin();it!=mp[temp].end();it++){
            //     cout<<it->first<<" "<<it->second<<"\n";
            // }
        }
    }
    
    // Set up the lines of text
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Output");

    // Set up the output display
    sf::Font font;
    font.loadFromFile("arial.ttf");
    
    std::vector<std::string> lines{"data structure used is priority queue"};
    while(!pq.empty()){
        o temp=pq.top();
        pq.pop();
        // cout<<temp.s<<" "<<temp.score<<"\n";
        string str=temp.s;
        int score=temp.score;
        string s=temp.s+" "+to_string(temp.score);
        lines.push_back(s);
    }
    std::vector<sf::Text> textLines;


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // cout << "\nTime taken by function : "<< duration.count() << " microseconds";
    lines.push_back("time taken is "+ to_string(duration.count())+" microseconds");
    for (int i = 0; i < lines.size(); i++) {
        sf::Text line(lines[i], font, 24);
        line.setPosition(20.0f, 20.0f + 30.0f * i);
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
// void printbest2(string s){

// }
void printbest2(string s){
     auto start = high_resolution_clock::now();
    set<string> uniqueSubsequences;
    map<int,vector<string>> tree;
    findUniqueSubsequences(s, 0, "", uniqueSubsequences);

    for(string t:uniqueSubsequences){
        
        if(mp.find(t)!=mp.end()){
    //         //put in priority queue
            // cout<<"inserting in pq"<<"\n";
            for(auto it=mp[t].begin();it!=mp[t].end();it++){
                //add to tree here
                int score=it->second;
                string str=it->first;
                if(tree.find(score)!=tree.end()){
                    tree[score].push_back(str);
                }
                else{
                    vector<string> v={str};
                    tree[score]=v;
                }
            }
            // for(auto it:mp[temp].begin();it!=mp[temp].end();it++){
            //     cout<<it->first<<" "<<it->second<<"\n";
            // }
        }
    }
     sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Output");

    // Set up the output display
    sf::Font font;
    font.loadFromFile("arial.ttf");
    
    std::vector<std::string> lines{"data structure used is ordered_map(tree)"};
    
    
    for(auto it=tree.rbegin();it!=tree.rend();it++){
        int score=it->first;
        for(int i=0;i<it->second.size();i++){
            lines.push_back(it->second[i]+" "+to_string(score));
        }
    }
     std::vector<sf::Text> textLines;
    auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
//    cout << "\nTime taken by function : "<< duration.count() << " microseconds";
   lines.push_back("time taken is "+ to_string(duration.count())+" microseconds");
    for (int i = 0; i < lines.size(); i++) {
        sf::Text line(lines[i], font, 24);
        line.setPosition(20.0f, 20.0f + 30.0f * i);
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
    return;
}
int main() {
    // Read in the dictionary file
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Window");

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
    string line;
    ifstream myfile("dictionary.txt");
    ///reading the file
    if(myfile.is_open()){
        while(getline(myfile, line)){
            int sc=calculate_score(line);
            string temp=line;
            mergesort(temp,0,temp.length()-1);
            // cout<<"line= "<<line<<"temp= "<<temp<<"\n";
            if(mp.find(temp)!=mp.end()){
                // Node x={line ,sc};
                mp[temp][line]=sc;
                // cout<<"existing in map"<<endl;
            }
            else{
                
                // Node x={line,sc};
                unordered_map<string,int> t;
                t[line]=sc;
                mp[temp]=t;
                // cout<<"inserted in map"<<endl;
            }
        }
        myfile.close();
    }
    // for (auto it=mp.begin();it!=mp.end();it++){
    //     cout<<it->first<<" \n";
    // }
   
    // for(auto it=mp["AA"].begin();it!=mp["AA"].end();it++){
    //     cout<<it->first<<" "<<it->second<<"\n";
    // }
    printbest1(input);
    printbest2(input);
    return 0;
}
