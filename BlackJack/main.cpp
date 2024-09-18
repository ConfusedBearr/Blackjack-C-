//Coded By Rodrigo Peixoto
//Coded On 04/02/2023
//Purpose To Play Black Jack

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

struct Card{
    string value;
    string suits;
};

struct Deck{
    Card cards[52];
    int top_card_index = 51;
};

void initializeDeck(Deck& deck);
void shuffleDeck(Deck& deck);
void dealCards(Deck& deck, Card& player_card1, Card& player_card2, Card& player_card3, Card& player_card4,
               Card& dealer_card1, Card& dealer_card2, Card& dealer_card3,Card& dealer_card4);
int getCardValue(Card& card);
void displayMainMenu();
void displayRules();


int main() {
    long long totalBalance = 100;
    double wins = 0, losses = 0 , totalPlays = 0 , ties = 0;

    while (true) {
        int choice;
        do {
            displayMainMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    Deck deck;
                    initializeDeck(deck);
                    shuffleDeck(deck);
                    long long wager = 0;
                    totalPlays++;
                    cout << "Current Balance: $" << totalBalance << endl;
                    cout << "Enter the amount you like to wager: $";
                    cin >> wager;

                    Card player_card1, player_card2, dealer_card1, player_card3, player_card4, dealer_card2, dealer_card3, dealer_card4;

                    dealCards(deck, player_card1, player_card2, dealer_card1, player_card3, player_card4,
                              dealer_card2, dealer_card3, dealer_card4);

                    int playerHand = getCardValue(player_card1) + getCardValue(player_card2);
                    // determine the value of the dealer's hand
                    int dealer_value;
                    dealer_value = getCardValue(dealer_card1) + getCardValue(dealer_card2);

                    cout << "\tYour hand is: " << player_card1.value << " and " << player_card2.value;
                    // print the dealer's hand
                    cout << "\t\t\tDealer's hand: " << dealer_card1.value << " and  " << dealer_card2.value << endl;

                    cout << "\tYour hand's value: " << playerHand;
                    cout << "\t\t\t\tDealer's hand value is: " << dealer_value << endl;
                    bool did_stand = false;
                    // asks the player is they want to hit or stand
                        char action;
                        cout << "Would you like to hit or stand? (H/S) ";
                        cin >> action;

                        if (action == 'H' || action == 'h') {
                            cout << "You drew: " << player_card3.value << endl;
                            playerHand += getCardValue(player_card3);

                            cout << "Hand Value: " << playerHand << endl;

                            if (playerHand > 21) {
                                cout << "Player is bust! Dealer wins!" << endl;
                                totalBalance -= wager;
                                losses--;
                                break;
                            }

                        } else if (action == 'S' || action == 's') {
                                did_stand = true;
                        } else {
                            cout << "Invalid action. Please enter hit or stand. (H/S)" << endl;
                        }

                    // makes the dealer hit if they under 17
                    if (dealer_value < 17) {
                        cout << "Dealer draws: " << dealer_card3.value << endl;
                        dealer_value += getCardValue(dealer_card3);
                        cout << "Dealers hand value: " << dealer_value << endl;
                        if (dealer_value > 21) {
                            cout << "Dealer is bust! Player wins!" << endl;
                            totalBalance += wager;
                            wins++;
                            break;
                        }
                    }

                    // asks the player is they want to hit and if they stood before this wont show up
                    if(playerHand < 21 && did_stand == false) {
                        char action;
                        cout << "Would you like to hit or stand? (H/S) ";
                        cin >> action;

                        if (action == 'H' || action == 'h') {
                            cout << "You drew: " << player_card4.value << endl;
                            playerHand += getCardValue(player_card4);

                            cout << "Hand Value: " << playerHand << endl;

                            if (playerHand > 21) {
                                cout << "Player is bust! Dealer wins!" << endl;
                                totalBalance -= wager;
                                losses--;
                                break;
                            }

                        } else if (action == 'S' || action == 's') {


                        } else {
                            cout << "Invalid action. Please enter hit or stand. (H/S)" << endl;
                        }
                    }

                    // makes the dealer hit if they under 17
                    if (dealer_value < 17) {
                        cout << "Dealer draws: " << dealer_card4.value << endl;
                        dealer_value += getCardValue(dealer_card4);
                        cout << "Dealers hand value: " << dealer_value;
                        if (dealer_value > 21) {
                            cout << "Dealer is bust! Player wins!" << endl;
                            totalBalance += wager;
                            wins++;
                            break;
                        }
                    }

                    // compare the hands to determine the winner
                    if (playerHand > dealer_value && playerHand <= 21) {
                        cout << "Player wins!" << endl;
                        totalBalance += wager;
                        wins++;

                    } else if (playerHand < dealer_value && dealer_value <= 21) {
                        cout << "Dealer wins!" << endl;
                        totalBalance -= wager;
                        losses++;
                    } else {
                        cout << "It's a tie!" << endl;
                        ties++;
                    }
                    break;

                }
                case 2:
                    displayRules(); // displayed the rules of the game
                    break;
                case 3:
                    // Allows the user to enter a large amount of money
                    long long deposit;
                    cout << "Your current balance is: $" << totalBalance << endl;
                    cout << "How much would like to deposit: $";
                    cin >> deposit;
                    totalBalance += deposit;
                    cout << "Your new balance is: $" << totalBalance << endl;
                    break;
                case 4:
                    // allows the user to withdrawal
                    long long withdrawal;
                    cout << "Your current balance is $" << totalBalance << endl;
                    while (true) {
                        cout << "How much would you like to withdraw: $";
                        cin >> withdrawal;

                        if (totalBalance < withdrawal) {
                            cout << "Not enough money, please enter a valid amount." << endl;
                        } else {
                            totalBalance -= withdrawal;
                            cout << "Your new balance is: $" << totalBalance << endl;
                            break; // exit the loop when a valid amount is entered
                        }
                    }
                    break;
                case 5:
                    // shows the win, losses, ties, and win %
                    cout << "Here are your stats for winning and losing this BJ session!" << endl;
                    cout << "Wins: " << wins << endl;
                    cout << "Losses: " << losses << endl;
                    cout << "Ties: " << ties << endl;
                    cout << "Win %: " << round(wins/losses) << endl;
                    break;
                case 6:
                    // quits the program
                    cout << "Thank You For Playing!" << endl;
                    return 0;
                default:
                    // doesnt allow user to enter a incorrect number
                    cout << "Invalid Option Please Try Again (1-6)";

            }
        } while (choice == 6);
    }
}


void initializeDeck(Deck& deck){
    string suits[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string values[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    int card_index = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            Card card;
            card.suits = suits[i];
            card.value = values[j];
            deck.cards[card_index] = card;
            card_index++;
        }
    }
    deck.top_card_index = 51;
}

void shuffleDeck(Deck& deck){  // shuffle the deck
    srand(time(NULL));
    for (int i = 0; i < 52; i++) {
        int j = rand() % 52;
        Card temp = deck.cards[i];
        deck.cards[i] = deck.cards[j];
        deck.cards[j] = temp;
    }
}

void dealCards(Deck& deck, Card& player_card1,Card& player_card2,Card& dealer_card1,Card& player_card3,Card& player_card4,
               Card& dealer_card2,Card& dealer_card3,Card& dealer_card4) {
    // Deal first card to player
    if (deck.top_card_index >= 0) {
        player_card1 = deck.cards[deck.top_card_index--];
    }

    // Deal first card to dealer
    if (deck.top_card_index >= 0) {
        dealer_card1 = deck.cards[deck.top_card_index--];
    }

    // Deal second card to player
    if (deck.top_card_index >= 0) {
        player_card2 = deck.cards[deck.top_card_index--];
    }

    // Deal second card to dealer
    if (deck.top_card_index >= 0) {
        dealer_card2 = deck.cards[deck.top_card_index--];
    }

    if (deck.top_card_index >= 0) {
        player_card3 = deck.cards[deck.top_card_index--];
    }

    if (deck.top_card_index >= 0) {
        dealer_card3 = deck.cards[deck.top_card_index--];
    }

    if (deck.top_card_index >= 0) {
        player_card4 = deck.cards[deck.top_card_index--];
    }

    if (deck.top_card_index >= 0) {
        dealer_card4 = deck.cards[deck.top_card_index--];
    }
}

int getCardValue(Card& card) {
    string card_value = card.value;
    if (card_value == "Ace") {
        return 11;
    } else if (card_value == "King" || card_value == "Queen" || card_value == "Jack") {
        return 10;
    } else if (card_value == "10" || card_value == "9" || card_value == "8" || card_value == "7" ||
            card_value == "6" || card_value == "5" || card_value == "4" || card_value == "3" || card_value == "2") {
        return stoi(card_value);
    } else {
        return -1;  // invalid card value
    }

}

void displayMainMenu(){ // displays the main menu
    cout << "\n\tWelcome to BlackJack!" << endl;
    cout << "1. Play BlackJack" << endl;
    cout << "2. Rules" << endl;
    cout << "3. Add to balance" << endl;
    cout << "4. Withdraw from balance" << endl;
    cout << "5. Statics" << endl;
    cout << "6. Quit" << endl;
    cout << "Enter an option from above (1-6): ";
}

void displayRules(){ //displays the rules
    cout << "Rules. Blackjack hands are scored by their point total. \nThe hand with the highest total wins as long as it doesn't exceed 21;\n "
            "a hand with a higher total than 21 is said to bust. \nCards 2 through 10 are worth their face value, and face cards "
            "(jack, queen, king) are also worth 10." << endl;
}