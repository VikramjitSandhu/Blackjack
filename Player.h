/**
    Player.h
    Purpose: Represents a player. Keeps track of the chips remaining with the user after completing
             a round of Blackjack, the amount of money bet in each round and the number of hands the player
             is playing. A player always has at least 1 hand and if he deices to split (under right conditions)
             ha can get upto two hands.

    @author Vikramjit Sandhu
*/

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "Card.h"
#include "Hand.h"

#define TOTAL_PLAYER_CHIPS 100

class Player
{
    //the starting chips for the player
    int totalChips;

    //the chips available to the user after one round
    int remainingChips;

    //the amount of chips remaining to the user
    int currentBet;

    /**represents the splits hands for the player. If the player does
    not chose to split, they have only one hand. If he splits, he has two hands.
    Since the (implemented) game rules do not allow splitting after the initial
    hand, the player cannot have more than two split hands*/

    Hand hands[2];

public:
    //default constructor
    Player();

    /**resets the parameters of the player object if the player decides to continue
    after one round. Basically this function sets currentBet=0
    as well as calls the reinitialize function on the hand objects.
    @return void
    @param
    */
    void reintialize();

    /**updates the chips available to the player after one round
    @return void
    @param the amount of chips won or lost
    */
    void updateRemainingChips(int value)
    {
        remainingChips = remainingChips + value;
    }

    /**gets the chips remaining with the player
    @return available chips
    @param
    */
    int getRemainingChips()
    {
        return remainingChips;
    }

    /**returns the first hand of the player
    @return the hand object
    @param
    */
    Hand getFirstHand()
    {
        return hands[0];
    }

    /**returns the second hand of the player
    @return the hand object
    @param
    */
    Hand getSecondHand()
    {
        return hands[1];
    }

    /**updates the number of chips bet by the player
    @return void
    @param the chips bet by the user
    */
    void updateCurrentBet(int bet)
    {
        currentBet+=bet;
    }

    /**returns the amount of chips bet by the player
    @return the chips bet
    @param
    */
    int getCurrentBet()
    {
        return currentBet;
    }

    /**returns the initial number of chips available to the player
    @return the total chips
    @param
    */
    int getTotalChips()
    {
        return totalChips;
    }
};


#endif // PLAYER_H_INCLUDED
