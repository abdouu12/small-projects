#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;
void custom_print(string var){
    cout << "-" << var << "\n";
}
void clear_consol(){
    cout << "\033[2J\033[1;1H"; 
}
int generate_random_number(int min, int max) {
    // Random number generator initialization
    random_device rd;  // Initialize a random device
    mt19937 gen(rd()); // Initialize a Mersenne Twister pseudo-random generator
    uniform_int_distribution<> dis(min, max);  // Uniform distribution between min and max

    return dis(gen);  // Generate and return the random number
}


void user_input(string& input) {
    custom_print("move");
    cin >> input;
}
void remove_card (vector<string>& deck, string& input){
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
    for (int i = 0; i< deck.size(); i++)
    {
        cout << deck[i] << " ";
    }
    cout << "\n";
}
vector<string> initialize_original_card(vector<string>& initial_card_holder,vector<string>& draw_deck) {
    initial_card_holder.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    return initial_card_holder;
}
vector<string> initialize_player_deck(vector<string>& player_deck,vector<string>& draw_deck) {
    player_deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    player_deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    player_deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    player_deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    player_deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
 
    return player_deck;
}
vector<string> initialize_bot_deck(vector<string>& bot_deck,vector<string>& draw_deck) {
    bot_deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    bot_deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    bot_deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    bot_deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
    bot_deck.push_back(draw_deck[generate_random_number(1,draw_deck.size())]);
 
    return bot_deck;

}
vector<string> initialize_drawing_deck(vector<string>& draw_deck) {
    string colours[] = {"R","B","G","Y"};
    for (int i = 0; i< 4; i++) {
        for (int j = 0; j< 10; j++) {
        draw_deck.push_back(colours[i] + to_string(j));
        }
    }
    return draw_deck; 
}
//special cards
void change_colour(vector<string>& initial_card_holder){
    custom_print("what colour? R,B,Y,G");
    char colour_input;
    cin >> colour_input;
    string card = initial_card_holder[0];
    card[0] = colour_input;
    initial_card_holder[0] = card[0];
    
}
void plus_card(){

}
void swap_cards() {

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
void bot_logic(vector<string>& bot_deck, vector<string>& initial_card_holder, vector<string>& draw_deck) {
    string card = initial_card_holder[0];
    char card_color = card[0];
    char card_number = card[1];
    int count = 0;
    for (int i = 0; i < bot_deck.size(); i++) {
        string bot_card = bot_deck[i];
        char bot_colr = bot_card[0];
        char bot_num = bot_card[1];
        if (card_color == bot_colr || card_number == bot_num) {
            initial_card_holder[0] = bot_deck[i];
            bot_deck.erase(bot_deck.begin() + i);
            count++;
            return;
        } 
    }
    if (count == 0) {
        bot_deck.push_back(draw_deck[0]);
        draw_deck.erase(draw_deck.begin());
    }

}
int main () {
    bool gamerunning = true;
    string input;
    vector<string> player_deck;
    vector<string> draw_deck;
    vector<string> bot_deck;
    vector<string> initial_card_holder;
    initialize_drawing_deck(draw_deck);
    initialize_player_deck(player_deck,draw_deck);
    initialize_original_card(initial_card_holder,draw_deck);
    initialize_bot_deck(bot_deck,draw_deck);
    display_deck(player_deck);
    while (gamerunning) {
        shuffle_deck(draw_deck);
        //start of turn 
        custom_print("here is the original card, you can start!");
        display_deck(initial_card_holder);     
        

        user_input(input);
        if (match_card(initial_card_holder,input,player_deck) ){
            remove_card(player_deck,input);
            initial_card_holder[0] = input;
        }
        else{
            custom_print("card doesn't match, draw card if you don't have any!");
            draw_a_card(player_deck,draw_deck);
        }
        if (draw_deck.empty()) {
            initialize_drawing_deck(draw_deck);
        }
        //end of turn
        clear_consol();
        custom_print("these are your cards");
        display_deck(player_deck);

        custom_print("this is the bot card");
        display_deck(bot_deck);
        bot_logic(bot_deck,initial_card_holder,draw_deck);
        game_over(player_deck,gamerunning,bot_deck);

    }
    
    return 0;
}