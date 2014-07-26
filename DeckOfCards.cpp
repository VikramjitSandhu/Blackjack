/**
    DeckofCards.cpp
    Purpose: Represents a deck of cards used to play the  game of blackjack
    @author Vikramjit Sandhu
*/


#include "Card.h"
#include "DeckOfCards.h"

void DeckOfCards::createDeck(string suites[],int len, Card stackOfCards[])
{
    //variable to determine position in the array of representing the deck of cards in which the new card is put.
    int pos = 0;

    //the card types in a deck
    string cardTypes[] = {"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};

    //the points for each of the 13 cards independent of suite
    int points[] = {11,2,3,4,5,6,7,8,9,10,10,10,10};

    //outer for loop for each suite. each iteration generates the 13 cards in the suite
    for(int i=0;i<len;i++)
    {
        //each iteration generates a card in a suite
        for(int j=0;j<CARDS_IN_SUITE;j++)
        {
            // if the card is an ace of any suite
            if(j==0)
            {
                stackOfCards[pos++]=Card(cardTypes[j],points[j],suites[i],0,1);
            }
            //card not an ace and not a King, Queen or Jack
            else if(j>0 &&j<10)
            {
                stackOfCards[pos++]=Card(cardTypes[j],points[j],suites[i],0,0);
            }
            //card is a King Queen or Jack of any suite
            else
            {
                stackOfCards[pos++]=Card(cardTypes[j],points[j],suites[i],1,0);
            }
        }
    }
}

//Knuth shuffle of an array. Each of the 52! combinations are equally likely to be generated
void DeckOfCards::shuffleDeck(Card stackOfCards[], int len)
{
    //tem variable used for exchanging
    Card temp;

    //seed to generate a random number
    time_t now;
    time(&now);
    srand((unsigned int)now);
    for(int i=0;i<len;i++)
    {
        int r = rand() % len;
        temp = stackOfCards[r];
        stackOfCards[r] = stackOfCards[i];
        stackOfCards[i] = temp;
    }
}

Card DeckOfCards::drawCardAtPos(int position)
{
    return stackOfCards[position];
}

void DeckOfCards::printStack(Card deck[], int len)
{
    cout<<"-------------Printing stack of cards-------------"<<endl;
    for(int i=0;i<len;i++)
    {
        cout<<i<<" card is "<<deck[i].getCardType()<<" of "<<deck[i].getSuite()<<endl;
    }
}

void DeckOfCards::shuffleForSplit(Card stackOfCards[], int len)
{
    //cout<<"-----------------------SPLIT TEST----------------"<<endl;
    Card card0 = stackOfCards[0];
    Card card1 = stackOfCards[1];
    Card temp;

    if(card1.isAce()==1)
    {
        if(card0.isAce()==1)
        {
            temp = stackOfCards[0];
            stackOfCards[0] = stackOfCards[3];
            stackOfCards[3] = temp;
        }
        else
        {
            for(int j=2;j<len;j++)
            {
                temp = stackOfCards[j];
                if(temp.isAce()==1)
                {
                    stackOfCards[j] = stackOfCards[3];
                    stackOfCards[3] = temp;
                }
            }
        }
    }

    else if(card1.isFaceCard()==1)
    {
        if(card0.isFaceCard()==1 && (card0.getCardType() == card1.getCardType()))
        {
            temp = stackOfCards[0];
            stackOfCards[0] = stackOfCards[3];
            stackOfCards[3] = temp;
        }
        else
        {
            for(int j=2;j<len;j++)
            {
                temp = stackOfCards[j];
                if(temp.isFaceCard()==1 && (temp.getCardType() == card1.getCardType()))
                {
                    stackOfCards[j] = stackOfCards[3];
                    stackOfCards[3] = temp;
                }
            }
        }
    }

    else if(card1.isFaceCard()==0 && card1.isAce()==0)
    {
        if(card0.isFaceCard()==0 && (card0.getPoints() == card1.getPoints()))
        {
            temp = stackOfCards[0];
            stackOfCards[0] = stackOfCards[3];
            stackOfCards[3] = temp;
        }
        else
        {
            for(int j=2;j<len;j++)
            {
                temp = stackOfCards[j];
                if(temp.isFaceCard()==0 && (temp.getPoints() == card1.getPoints()))
                {
                    stackOfCards[j] = stackOfCards[3];
                    stackOfCards[3] = temp;
                }
            }
        }
    }
}
