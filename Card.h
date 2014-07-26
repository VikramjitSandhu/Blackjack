/**
    Card.h
    Purpose: Represents an object of type card (e.g. 2 of Hearts, King of Clubs etc.) in a deck of cards

    @author Vikramjit Sandhu
*/


#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <iostream>
using namespace std;

class Card
{
private:
    /*A string representing the number on the card e.e "Two", "Three" etc. Used mainly to
    draw a graphical representation of the card*/
    string cardType;

    // the suite(hearts, spades , clubs. diamonds) to which the card belongs
    string suite;

    //the points allocated to the card
    int points;

    //is the card a King, Queen or Jack of any suite
    int faceCard;

    //is the card an ace
    int ace;

public:
    //default constructor: constructs a blank card
    Card(){}

    //constructor to create a card of a certain suite. also allocates points to it
    Card(string cardType, int points, string suite, int faceCard, int ace);

    //setter and getter functions of the card class
    /**get the card type
    @return string representing the card type
    @param */
    string getCardType()
    {
        return cardType;
    }

    /**get the suite of the card
    @return: string representing the suite
    @param */
    string getSuite()
    {
        return suite;
    }

     /**get the poinys of the card
    @return integer representing the points
    @param */
    int getPoints()
    {
        return points;
    }

    /**set the points
    @return void
    @param points: points for the card*/
    void setPoints(int points)
    {
        this->points = points;
    }

    /**check if card is a King, Queen or Jack of any suite
    @return 1: card is one of the above
            0: card is not one of the above
    @param */
    int isFaceCard()
    {
        return faceCard;
    }

    /**check if card is a Ace any suite
    @return 1: card is an ace
             0: card is not an ace
    @param */
    int isAce()
    {
        return ace;
    }

    /**draw a simple graphical representation of the card
    @return void
    @param position from the left edge of the screen where the drawing will start
    @param position from the top edge of the screen where the drawing will start
    @param is the card to be drawn the frst dealer card. This card will be shown as unknown to the player
    @param The type of the card
    @param the choice of the player to allow or disallow drawing the card
        1: allow graphics
        0: only allow text*/
    void drawCard(int,int,int, string, int);
};

#endif // CARD_H_INCLUDED
