/**
    DeckOfCards.cpp
    Purpose: Represents the dealer in the  game of blackjack

    @author Vikramjit Sandhu
*/

#include "Dealer.h"

Dealer::Dealer()
{
    //in the beginning dealer has not accumulated any points
    currentTotal = 0;
    //in the beginning dealer has not drawn any cards
    totalCards = 0;
    //in the beginning dealer is not bust
    bust = 0;
}

void Dealer::reintialize()
{
    bust = 0;
    currentTotal = 0;
    totalCards = 0;
}

void Dealer::setTotal(Card c)
{
    currentTotal+=c.getPoints();
    dealerCards[totalCards++] = c;
}


Card Dealer::drawCardAtPos(DeckOfCards doc, int position)
{
    return doc.drawCardAtPos(position);
}
