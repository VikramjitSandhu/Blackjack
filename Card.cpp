/**
    Card.cpp
    Purpose: Represents an object of type card (e.g. 2 of Hearts, King of Clubs etc.) in a deck of cards

    @author Vikramjit Sandhu
*/


#include "Card.h"

Card::Card(string cardType, int points, string suite, int faceCard, int ace)
{
    this->cardType = cardType;
    this->points = points;
    this->suite = suite;
    this->faceCard = faceCard;
    this->ace = ace;
}

void Card::drawCard(int horzOffset, int vertOffset, int isDealerFirstCard, string type, int graphicsOn)
{
    string cardType = this->cardType;
    string suite = this->suite;
    int points = this->points;
    int faceCard = this->faceCard;
    int ace = this->ace;

    if(graphicsOn==1)
    {
        for(int i=0;i<vertOffset;i++) cout<<endl;
        for(int i=0;i<horzOffset;i++) cout<<" ";

        for(int i=0;i<6;i++) cout<<"-";
        cout<<endl;

        for(int i=0;i<horzOffset;i++) cout<<" ";
        if(isDealerFirstCard==0)
        {
            if(ace==1)
                cout<<"|A   |"<<endl;
            else if(faceCard == 1)
                cout<<"|"<<cardType[0]<<"   |"<<endl;
            else
                cout<<"|"<<points<<"   |"<<endl;
        }
        else
            cout<<"|U   |"<<endl;

        for(int i=0;i<horzOffset;i++) cout<<" ";
        cout<<"|    |"<<endl;

        for(int i=0;i<horzOffset;i++) cout<<" ";
        if(isDealerFirstCard==0)
            cout<<"|  "<<suite[0]<<" |"<<endl;
        else
            cout<<"|  "<<"U"<<" |"<<endl;

        for(int i=0;i<horzOffset;i++) cout<<" ";
        cout<<"|    |"<<endl;

        for(int i=0;i<horzOffset;i++) cout<<" ";
        if(isDealerFirstCard==0)
        {
            if(ace==1)
                cout<<"|   A|"<<endl;
            else if(faceCard == 1)
                cout<<"|   "<<cardType[0]<<"|"<<endl;
            else
                cout<<"|   "<<points<<"|"<<endl;;
        }
        else
            cout<<"|   U|"<<endl;;

        for(int i=0;i<horzOffset;i++) cout<<" ";
        for(int i=0;i<6;i++)
        {
            cout<<"-";
        }
        cout<<endl;
    }

    if(isDealerFirstCard==0)
        cout<<type<<" received a "<<cardType<<" of "<<suite<<endl;
    else
        cout<<"unknown card for dealer received "<<endl;
}
