/**
    Hand.cpp
    Purpose: Represents a hand played by the player. A hand is merely
    the bunch/set of cards drawn by the user. If the user decides to split,
    he gets a total of two hands

    @author Vikramjit Sandhu
*/

#include "Hand.h"

Hand::Hand()
{
    currentTotal = 0;
    totalCards = 0;
    bust = 0;
    valid = 0;
    win = 0;
}

void Hand::setTotal(Card c)
{
    currentTotal+=c.getPoints();
    handCards[totalCards++] = c;
}

void Hand::reintialize()
{
    currentTotal = 0;
    totalCards = 0;
    bust = 0;
    valid = 0;
    win = 0;
}
