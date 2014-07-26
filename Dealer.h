/**
    DeckOfCards.h
    Purpose: Represents the dealer in the  game of blackjack
             keeps track of the cards dealt to the dealer, the accumulated points
             and if dealer has bust or not

    @author Vikramjit Sandhu
*/

#ifndef DEALER_H_INCLUDED
#define DEALER_H_INCLUDED

#include "Card.h"
#include "DeckOfCards.h"

class Dealer
{
    /**array keeping track of the cards drawn by the dealer.
       The length is chosen as 11 because the dealer cannot have
       more than 11 cards before the total points exceed 21
       4 aces+4 twos + 3 threes*/
    Card dealerCards[11];

    /**variable representing the total points accumulated
       by the player after drawing the latest card. Updated
       every time the dealer draws a card*/
    int currentTotal;

    /**variable keeping track of the cards drawn by the user.
       updated every time the dealer draws a card*/
    int totalCards;

    //variable keeping track if the dealer busts (total points > 21)
    int bust;

public:

    //default constructor for the Dealer object
    Dealer();

    /**reset the parameters of the Dealer at the start of a new game
    namely, sets totalCards, currentTotal and bust = 0
    @return void
    @param
    */
    void reintialize();

    /**updates the points accumulated by the dealer
    @return void
    @param Card: the latest card object drawn by the dealer
    */
    void setTotal(Card c);

    /**returns the points accumulated by the dealer
    @return the total
    @param
    */
    int getTotal()
    {
        return currentTotal;
    }

    /**returns card object from the deck of cards
    @return the card specified at a position in the deck of cards
    @param the deck of cards from which the card needs to be drwan
    @param the position in the deck at which to draw the card
    */
    Card drawCardAtPos(DeckOfCards d, int pos);

    /**returns the first card drawn by the dealer
    @return the first card drawn by the dealer. The player cannot see the card
    @param
    */
    Card getUnknownCard()
    {
        return dealerCards[0];
    }

    /**indicates that the dealer busts i.e. the total points drawn by the dealer exceeds 21
    @return
    @param b = 1 indicates dealer has bust
           b = 0 dealer has not bust
    */
    void setBust(int b)
    {
        bust = b;
    }

    /**check to see if dealer has bust
    @return dealer bust
            1: dealer buts
            0: dealer not bust
    @param
    */
    int getBust()
    {
        return bust;
    }

};


#endif // DEALER_H_INCLUDED
