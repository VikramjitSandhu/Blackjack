/**
    DeckOfCards.h
    Purpose: Represents a deck of cards used to play the  game of blackjack

    @author Vikramjit Sandhu
*/

#ifndef DECKOFCARDS_H_INCLUDED
#define DECKOFCARDS_H_INCLUDED

#include <cstdlib>
#include<time.h>

#define CARDS_IN_DECK 52
#define SUITES_IN_DECK 4
#define CARDS_IN_SUITE CARDS_IN_DECK/SUITES_IN_DECK

class DeckOfCards
{
private:
    //Each deck of cards object contains 52 objects of type card
    Card stackOfCards[CARDS_IN_DECK];
    //the suites in the deck of cards
    string suitesInDeck[SUITES_IN_DECK];

public:
    //constructor of the deck of cards object. Creates the 52 cards in the deck and then shuffles them
    DeckOfCards()
    {
        suitesInDeck[0] = "Hearts";
        suitesInDeck[1] = "Spades";
        suitesInDeck[2] = "Clubs";
        suitesInDeck[3] = "Diamonds";
        createDeck(suitesInDeck,SUITES_IN_DECK,stackOfCards);
        shuffleDeck(stackOfCards,CARDS_IN_DECK);

        /*The following function is a function which generates a shuffled deck where the player always received
          two similar cards in the first two draws. Commented out for demo purposes. Uncomment to check if split works.*/
        //shuffleForSplit(stackOfCards,CARDS_IN_DECK);

        /*prints out the shuffled deck of cards. used for testing purposes and commented out for the demo version.*/
        //printStack(stackOfCards,CARDS_IN_DECK);
    }

    /**create the deck of cards.
    @return void
    @param an array containing the 4 suites in the deck
    @param the length of the array of suites
    @param the array that will contain each of the 52 cards*/
    void createDeck(string suitesInDeck[],int length, Card stackOfCards[]);

    /**create the deck of cards.
    @return void
    @param the unshuffled array containing the 52 cards in a deck
    @param the number of cards in the deck*/
    void shuffleDeck(Card stackOfCards[], int len);

    /**
    function used only for testing purposes.*/
    void shuffleForSplit(Card stackOfCards[], int len);

    /**
    function used to print the cards in a deck. Used for testing purposes only*/
    void printStack(Card stackOfCards[], int len);

    /**draw a card from the shuffled deck of cards
    @return an object of type card from the deck of cards
    @param position in the deck of cards from which to draw a card*/
    Card drawCardAtPos(int position);
};

#endif // DECKOFCARDS_H_INCLUDED
