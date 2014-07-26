/**
    Hand.h
    Purpose: Represents a hand played by the player. A hand is merely
    the bunch/set of cards drawn by the user. If the user decides to split,
    he gets a total of two hands other wise the player always has at least 1 hand
    Keeps track of the points accumulated by a player hand, if the hand bust or not,
    if it is a valid hand (mainly to signify is the player split or not)

    @author Vikramjit Sandhu
*/

#ifndef HAND_H_INCLUDED
#define HAND_H_INCLUDED

#include "Card.h"

class Hand
{
    /**the cards drawn by the player. Each hand keeps a track
    of the cards drawn by the player. The length is chosen as
    11 because a hand  cannot have more than 11 cards before
    the total points exceed 21: 4 aces+4 twos + 3 threes*/
    Card handCards[11];

    //the total of the hand after drawing the latest card
    int currentTotal;

    //the total cards drawn by the player for the hand
    int totalCards;

    /**variable to keep track if the total points for the current
    hand exceeds 21.
    0: not bust
    1: bust*/
    int bust;

    /**variable to check if the hand is a valid hand. Used when the
    player decides to split his cards.
    0: not valid
    1: valid*/
    int valid;

    /**variable to keep track if this hand wins against the dealer or not
    1: win*/
    int win;

public:
    //default constructor
    Hand();

    /**updates the points accumulated by the user
    after drawing the latest card
    @return void
    @param the latest card drawn by the player for this hand
    */
    void setTotal(Card c);

    /**returns the total points accumulated by the player for this hand
    @return the points for this hand
    @param void
    */
    int getTotal()
    {
        return currentTotal;
    }

    /**indicates that the hand busts i.e. the total points drawn by the dealer exceeds 21
    @return
    @param b = 1 indicates hand has bust
           b = 0 hand has not bust
    */
    void setBust(int value)
    {
        bust = value;
    }

    /**check to see if this hand for the player has bust
    @return hand bust
            1: dealer buts
            0: dealer not bust
    @param
    */
    int getBust()
    {
        return bust;
    }

    /**sets the current hand as valid. used when the player decides to split cards
    @return void
    @param hand valid or not
           0: not a valid hand
           1: hand is valid
    */
    void setValid(int v)
    {
        valid = v;
    }

    /**checks if the current hand is valid. used when the player decides to split cards
    @return hand valid or not
           0: not a valid hand
           1: hand is valid
    @param void
    */
    int getValid()
    {
        return valid;
    }

    void setWin(int w)
    {
        win = w;
    }

    int getWin()
    {
        return win;
    }

    /**reset the parameters of the hand at the start of a new game
    namely, sets totalCards, currentTotal, bust, valid and win = 0
    @return void
    @param
    */
    void reintialize();
};


#endif // HAND_H_INCLUDED
