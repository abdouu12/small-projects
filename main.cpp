#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include "main.h"
#include <unordered_map>
using namespace std;
void custom_print(string var){
    cout << "-" << var << "\n";
}
void clear_consol(){
    cout << "\033[2J\033[1;1H"; 
}
int generate_random_number(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max - 1); // max - 1 to avoid out-of-bounds
    return dis(gen);
}
string findMajorityColor(vector<string>& deck) {
    int maxCount = 0;
    string majorityColor;
    unordered_map<std::string, int> colorCount;
    for (const auto& color : deck) {
    colorCount[color]++;
    if (colorCount[color] > maxCount) {
        maxCount = colorCount[color];
        majorityColor = color;
    }
    }
    return majorityColor;
}



void user_input(string& input) {
    custom_print("move");
    cin >> input;
}
void remove_card (vector<string>& deck, string input){
    int index;
    for (int i = 0; i < deck.size(); i++) {
        if (input == deck[i]) {
            index = i;
            break;
        }
        
    }
    deck.erase(deck.begin() + index);
}
void shuffle_deck(vector<string>& draw_deck) {
    random_device rd;  // Obtain a random number from hardware
    mt19937 gen(rd()); // Seed the generator
    shuffle(draw_deck.begin(), draw_deck.end(), gen);
}

void display_deck(vector<string>& deck) {
for (int i = 0; i < deck.size(); i++) {
    string card = deck[i];  
    char card_colour = card[0];  

    if (card_colour == 'R') {
        cout << "\033[31m" << card << "\033[0m" << " ";  // Red
    }
    else if (card_colour == 'B') {
        cout << "\033[34m" << card << "\033[0m" << " ";  // Blue
    }
    else if (card_colour == 'Y') {
        cout << "\033[33m" << card << "\033[0m" << " ";  // Yellow
    }
    else if (card_colour == 'G') {
        cout << "\033[32m" << card << "\033[0m" << " ";  // Green
    }
    else{
        cout << deck[i] << " ";
    }
}
cout << "\n";
}

vector<string> initialize_original_card(vector<string>& initial_card_holder,vector<string>& draw_deck) {
    initial_card_holder.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    return initial_card_holder;
}
vector<string> initialize_deck(vector<string>& deck,vector<string>& draw_deck) {
    deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
 
    return deck;
}
vector<string> initialize_drawing_deck(vector<string>& draw_deck, string add_card, string swap_card, string change_colour) {
    string colours[] = {"R","B","G","Y"};
    for (int i = 0; i< 4; i++) {
        for (int j = 0; j< 10; j++) {
        draw_deck.push_back(colours[i] + to_string(j));
        }
    }
    draw_deck.push_back(add_card);
    draw_deck.push_back(add_card);
    draw_deck.push_back(change_colour);
    draw_deck.push_back(change_colour);
    draw_deck.push_back(swap_card);
    draw_deck.push_back(swap_card);
    return draw_deck; 
}
//special cards
void change_colour(vector<string>& initial_card_holder,vector<string>& player_deck,vector<string>& bot_deck){
    custom_print("what colour? R,B,Y,G");
    char colour_input;
    cin >> colour_input;
    string card = initial_card_holder[0];
    card[0] = colour_input;
    initial_card_holder[0] = card[0];
    auto container = find(player_deck.begin(),player_deck.end(),"wild");
    if (container != player_deck.end()){
        remove_card(player_deck,"wild");
    }
    else if (container != bot_deck.end()) {
        remove_card(bot_deck,"wild");
    }
    
}
void plus_card(vector<string>& player_deck,vector<string>& bot_deck,vector<string>& draw_deck){
    bot_deck.push_back(draw_deck[0]);
    bot_deck.push_back(draw_deck[1]);

    auto container = find(player_deck.begin(),player_deck.end(),"add");
    if (container != player_deck.end()){
        remove_card(player_deck,"add");
    }
    else if (container != bot_deck.end()) {
        remove_card(bot_deck,"add");
    }

}
void swap_cards(vector<string>& player_deck,vector<string>& bot_deck) {
    vector<string> temp = player_deck;
    player_deck = bot_deck;
    bot_deck = temp;
    auto container = find(player_deck.begin(),player_deck.end(),"swap");
    if (container != player_deck.end()){
        remove_card(player_deck,"swap");
    }
    else if (container != bot_deck.end()) {
        remove_card(bot_deck,"swap");
    }
}
//checks
bool match_card(vector<string>& initial_card_holder, string& input, vector<string>& player_deck) {
    char card_colour_input = input[0];
    char card_number_input = input[1];
    string initial_card = initial_card_holder[0];
    char card_colour_initial = initial_card[0];
    char card_number_initial = initial_card[1];
    if (card_colour_input == card_colour_initial || card_number_initial == card_number_input) {
        return true;
    }
    return false;
}
void draw_a_card(vector<string>& player_deck,vector<string>& draw_deck) {
    player_deck.push_back(draw_deck[0]);
    draw_deck.erase(draw_deck.begin());
}
void game_over(vector<string>& player_deck,bool& gamerunning,vector<string>& bot_deck) {
    if (player_deck.empty()){
        custom_print("you win");
        gamerunning = false;
    }   
    else if (bot_deck.empty()) {
        custom_print("bot wins");
        gamerunning = false;
    }
}
//bot logic
void swap_bot_logic(vector<string>& player_deck,vector<string>& bot_deck){

    if (player_deck.size()>bot_deck.size()) {
        custom_print("the bot swapped your cards with his!");
        swap_cards(player_deck, bot_deck);
    }
}
void wild_card_bot_logic(vector<string>& initial_card_holder,vector<string>& bot_deck,vector<string>& player_deck) {
    string initial_card = initial_card_holder[0];

    char initial_card_colour = initial_card[0];
    int count = 0;
    for (int i=0; i<bot_deck.size();i++) {
        string bot_card = bot_deck[0];
        char bot_card_colour = bot_card[0];
        if (bot_card_colour != initial_card_colour) {
        count++;
        } 
    }
    if (count == 3) {
        initial_card_colour = findMajorityColor(bot_deck)[0];
    }
}
void add_card_bot_logic(vector<string>& player_deck,vector<string>& bot_deck, vector<string>& draw_deck) {
        player_deck.push_back(draw_deck[0]);
        player_deck.push_back(draw_deck[1]);
        
}

void bot_logic(vector<string>& bot_deck, vector<string>& initial_card_holder, vector<string>& draw_deck,vector<string>& player_deck) {
    auto it_swap = find(bot_deck.begin(),bot_deck.end(),"swap");
    auto it_wild = find(bot_deck.begin(),bot_deck.end(),"wild");
    auto it_add = find(bot_deck.begin(),bot_deck.end(),"add");
    string card = initial_card_holder[0];
    char card_color = card[0];
    char card_number = card[1];
    int count = 0;
    for (int i = 0; i < bot_deck.size(); i++) {
        string bot_card = bot_deck[i];
        char bot_colr = bot_card[0];
        char bot_num = bot_card[1];
        if (it_add != bot_deck.end()){
            add_card_bot_logic(player_deck,bot_deck,draw_deck);
            return;
        }
        if (it_swap != bot_deck.end()) {
            swap_bot_logic(player_deck,bot_deck);
            return;
        }
        if (card_color == bot_colr || card_number == bot_num) {
            initial_card_holder[0] = bot_deck[i];
            bot_deck.erase(bot_deck.begin() + i);
            count++;
            return;
        } 
    }
    if (count == 0) {
        if(it_wild != bot_deck.end()) {
            wild_card_bot_logic(initial_card_holder,bot_deck,player_deck);
        }
        else {
        bot_deck.push_back(draw_deck[0]);
        draw_deck.erase(draw_deck.begin());
        }

    }

}
int main () {
    bool gamerunning = true;
    string input;
    string wild_card = "wild";
    string add_card=  "add";
    string swap_card ="swap";
    vector<string> player_deck;
    vector<string> draw_deck;
    vector<string> bot_deck;
    vector<string> initial_card_holder;
    initialize_drawing_deck(draw_deck,add_card,swap_card,wild_card);
    initialize_deck(player_deck,draw_deck);
    initialize_deck(bot_deck,draw_deck);
    initialize_original_card(initial_card_holder,draw_deck);
    display_deck(player_deck);
    display_deck(bot_deck);
    while (gamerunning) {
        shuffle_deck(draw_deck);
        //start of turn 
        custom_print("here is the original card, you can start!");
        display_deck(initial_card_holder);     
        
        user_input(input);
        special_card_logic(input, add_card, player_deck, draw_deck, swap_card, bot_deck, wild_card, initial_card_holder);

        if (match_card(initial_card_holder,input,player_deck) ){
            remove_card(player_deck,input);
            initial_card_holder[0] = input;
        }
        else if (input == "d"){
            draw_a_card(player_deck,draw_deck);
        }
        if (draw_deck.empty()) {
            initialize_drawing_deck(draw_deck,add_card,swap_card,wild_card);
        }
        //end of turn
        clear_consol();
        custom_print("these are your cards");
        display_deck(player_deck);
        custom_print("this is the bot card");
       
        bot_logic(bot_deck,initial_card_holder,draw_deck,player_deck);
        display_deck(bot_deck);
        game_over(player_deck,gamerunning,bot_deck);

    }
    
    return 0;
}
void special_card_logic(std::string &input, std::string &add_card, std::vector<std::string> &player_deck, std::vector<std::string> &draw_deck, std::string &swap_card, std::vector<std::string> &bot_deck, std::string &wild_card, std::vector<std::string> &initial_card_holder)
{
    if (input == add_card)
    {
        plus_card(player_deck,bot_deck, draw_deck);
    }
    else if (input == swap_card)
    {
        swap_cards(player_deck, bot_deck);
    }
    else if (input == wild_card)
    {
        change_colour(initial_card_holder,player_deck,bot_deck);
    }
}