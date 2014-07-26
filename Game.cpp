/**
    Game.cpp
    Purpose: responsible for simulating the black jack game.
             deals cards to the player
             deals cards to the dealer
             decides who won
             gives option to the player to continue or quit

    @author Vikramjit Sandhu
*/


#include "Card.h"
#include "DeckOfCards.h"
#include "Player.h"
#include "Dealer.h"

class Game
{
    //object representing the dealer
    Dealer dealer;

    //object representing the player
    Player player;

    //object representing the deck of cards
    DeckOfCards doc;

    //variable tracking player's choice to hit or stand
    char playerChoice;

    //variable to track if player wants to continue playing
    char continuePlaying;

    //amount of chips bet by the player
    int playerBet;

    /**choice to user to switch on or switch off graphics
    choosing to switch off graphics will result in text messages only*/

    int graphicsOn;

public:
    //empty constructor
    Game()
    {
        //the player plays at least one round
        continuePlaying = 'y';

        //player bets at least 1 chip
        playerBet = 1;

        //by default graphics are switched off
        graphicsOn = 0;
    }

    void playInitialHand();
    int checkInitialHand(Player&, Hand, Card, Card);
    int checkForSamePlayerCards(Card, Card);
    void reinitializeGame(Player&, Dealer&);
    int checkForDealerBlackjack(Card dealerFirstCard, Card dealerSecondCard);
    int continueGame();
    void getPlayerBet();
    int calculatePlayerHandTotal(Player&, Hand&, int, DeckOfCards, int);
    int calculateDealerTotal(Dealer&, int, DeckOfCards);
    void checkConditions(Player&, Hand, Dealer, int);
    void drawTable();
    int getAceChoice();
    int playSingleGame(Player&, Hand&, DeckOfCards, Card, Card, Card, int);
    void setGraphics(int g);
};

/**sets the users choice to switch on or switch off graphics
@return void
@param user's choice*/
void Game::setGraphics(int g)
{
    graphicsOn = g;
}

/**returns the player's choice to continue playing or quitting
@return 0: player wants to quit. If the player has no more remaining chips
        he automatically quits
        1: player wants to and can continue
@param
*/
int Game::continueGame()
{
    //if the player has no more chips remaining
    //he automatically quits
    if(player.getRemainingChips()<1)
    {
        cout<<"You have no more remaining chips"<<endl;
        return 0;
    }
    char continuePlaying;
    cout<<"Do you wish to continue playing? Enter 'y' for yes; Any other key to stop"<<endl;
    cin>>continuePlaying;
    if(continuePlaying == 'y')
        return 1;
    else
        return 0;
}

/**check to see if the dealer has a blackjack based on the first two cards
dealt to the dealer
@return 1: dealer has blackjack
        0: dealer does not have blackjack
@param Card: the first card dealt to the dealer
@param Card: the second card dealt to the dealer
*/
int Game::checkForDealerBlackjack(Card dealerFirstCard, Card dealerSecondCard)
{
    cout<<"Checking for dealer BlackJack"<<endl;
    //if the first card has 10 points and the second card is an ace
    //the dealer has blackjack
    if((dealerSecondCard.getPoints()==10) && (dealerFirstCard.isAce()==1))
    {
        cout<<"face down card is an Ace. Dealer has Blackjack"<<endl;
        return 1;

    }
    //if the second card has 10 points and the first card is an ace
    //the dealer has blackjack
    else if((dealerSecondCard.isAce()==1) && dealerFirstCard.getPoints()==10)
    {
        cout<<"face down card has 10 points. Dealer has Blackjack"<<endl;
        return 1;
    }
    else
    {
        cout<<"Dealer does NOT have BlackJack"<<endl;
        return 0;
    }
}

/**sets the playerBet variable with the amount entered by the player
@return
@param
*/
void Game::getPlayerBet()
{
    cout<<"-------------------------------------------------"<<endl;
    cout<<"you currently have "<<player.getRemainingChips()<<" chips"<<endl;
    cout<<"Enter the amount to bet: 1, 5, 10"<<endl;
    cin>>playerBet;
    while(1)
    {
        //if the user enters a character input, ask to re-enter
        if(!cin)
        {
            cin.clear();
            cin.ignore();
            cout<<"Please enter a numeric input only"<<endl;
            cin>>playerBet;
        }
        else if(playerBet==1 || playerBet==5 || playerBet==10)
        {
            //check to see if the player has more than the number of chips bet
            //re-enter if insufficient funds
            if(playerBet>player.getRemainingChips())
            {
                cout<<"You only have "<<player.getRemainingChips()<<" chips left. Enter again"<<endl;
                cin>>playerBet;
            }
            else
            {
                player.updateCurrentBet(playerBet);
                cout<<"you bet "<<player.getCurrentBet()<<" chips"<<endl;
                break;
            }

        }
        //the player may bet 1, 5 or 10 chips only
        else
        {
            cout<<"you may only chose to bet 1, 5 or 10 chips. Please choose again"<<endl;
            cin>>playerBet;
        }
    }
}

/**allow the player to set the points for an ace of any suite
@return the points chosen by the player
@param
*/
int Game::getAceChoice()
{
    int aceChoice;
    cout<<"You drew an Ace. Do you wish to set it to 1 or 11 points?"<<endl;
    cin>>aceChoice;
    while(1)
    {
        //if the player enter a character, ask to enetr value again
        if(!cin)
        {
            cin.clear();
            cin.ignore();
            cout<<"Please enter a numeric input (1 or 11) only"<<endl;
            cin>>aceChoice;
        }
        else if(aceChoice==1 || aceChoice==11)
            return aceChoice;
        //if the player enters a number other than 1 or 11, ask to enter again
        else
        {
            cout<<"You may choose to set the value to 1 or 11 points only. Please enter again"<<endl;
            cin>>aceChoice;
        }
    }
}

/**calculates the points accumulated by the player for the current hand until he opts to stand or busts
@return the next position in the deck of cards from where a card will be drawn
@param Player&: a reference to the player object. passed as reference to allow changes to be
       reflected in the object
@param Hand&: a reference to the hand which the player is currently playing
@param cardToDraw: the position in the deck of cards from where the next card will be drawn
       for the player
@param DeckOfCards: the deck of cards containing the shuffled set of cards
@param gameNum: 1: represents the first split hand for the player
                2: represents the second split hand for the player
                3: represents the situation where either the player does not
                chose to split or the situation for splitting has not arisen
*/

int Game::calculatePlayerHandTotal(Player& player, Hand& playerHand, int cardToDrawAtPos, DeckOfCards doc, int gameNum)
{
    //the current card drawn by the user
    Card currCard;

    //horizontal offset at which to draw a card. only used if user chooses to switch on graphics
    int horzOffPlayerCard = 25;
    cout<<"Enter 's' to stand and any other key to hit"<<endl;
    cin>>playerChoice;

    //draw cards for the player until he hits 's' to stand
    while(playerChoice!='s')
    {
        //draw a card at the specified position from the deck of cards
        currCard = dealer.drawCardAtPos(doc, cardToDrawAtPos++);
        currCard.drawCard(horzOffPlayerCard,0,0,"Player",graphicsOn);

        //if the card drawn is an ace, give the player the option to set points
        if(currCard.isAce()==1)
        {
            //if choosing 11 points would lead to bust, automatically allocate 1 point to the ace card
            if((playerHand.getTotal()+currCard.getPoints())>21)
            {
                currCard.setPoints(1);
            }
            else
            {
                int aceValue = getAceChoice();
                currCard.setPoints(aceValue);
            }

        }

        //update the points accumulated by the player for this hand
        playerHand.setTotal(currCard);
        if(gameNum != 3)
            cout<<"the player's total points for game "<<gameNum<<" are: "<<playerHand.getTotal()<<endl;
        else
            cout<<"the player's total points are: "<<playerHand.getTotal()<<endl;

        //if the player's hand totals 21 points, do not draw any more cards for the player
        if(playerHand.getTotal()==21)
        {
            if(gameNum!=1)
                cout<<"Player total is 21. Dealer will now hit until win or bust"<<endl;
            break;
        }
        //player total exceeds 21. set the bust flag for this hand to 1
        //also update the player's total chips as he has lost his bet
        else if(playerHand.getTotal()>21)
        {
            cout<<"Bust: your total exceeds 21"<<endl;
            playerHand.setBust(1);
            cout<<"The player loses "<<playerBet<<" chips"<<endl;
            player.updateRemainingChips(-playerBet);
            break;
        }
        //player's total has not exceeded 21 yet. Give option to 'hit' or 'stand'
        else
        {
            cout<<"Enter 's' to stand and any other key to hit"<<endl;
            cin>>playerChoice;
        }
    }
    return cardToDrawAtPos;
}

/**calculates the points accumulated by the dealer until he opts to stand or busts
@return the next position in the deck of cards from where a card will be drawn
@param Dealer&: a reference to the dealer object. passed as reference to allow changes to be
       reflected in the object
@param cardToDraw: the position in the deck of cards from where the next card will be drawn
       for the player
@param DeckOfCards: the deck of cards containing the shuffled set of cards
*/

int Game::calculateDealerTotal(Dealer& dealer, int cardToDrawAtPos, DeckOfCards doc)
{
    cout<<endl;
    cout<<endl;

    //check the unknown card for the dealer
    Card currCard = dealer.getUnknownCard();
    cout<<"unknown card for dealer is: "<<currCard.getCardType()<<" of "<<currCard.getSuite()<<endl;
    int currentDealerTotal = dealer.getTotal();
    cout<<"The dealer's current points are "<<currentDealerTotal<<endl;

    //check to see if the total of the first two cards exceeds 21.
    //if yes, the dealer busts.set the bust flag to one
    if(currentDealerTotal>21)
    {
        dealer.setBust(1);
            cout<<"Bust: Dealer's total exceeds 21"<<endl;
        return cardToDrawAtPos;
    }

    // if the dealer has not bust, draw cards till the points accumulated by the dealer
    //exceed 17
    while(currentDealerTotal<17)
    {
        //draw a card from the deck of cards
        currCard = dealer.drawCardAtPos(doc,cardToDrawAtPos++);
        currCard.drawCard(1,0,0,"Dealer",graphicsOn);

        //if the most recently drawn cards results in the dealers points exceeding 21
        //check to see if it is an ace. if it is not an ace, the dealer busts
        if((currentDealerTotal+currCard.getPoints())>21)
        {
            //if the card is ace, set its points to 1 to avoid bust
            if(currCard.isAce()==1)
                currCard.setPoints(1);
            else
            {
                //set the bust flag to 1
                dealer.setBust(1);
                cout<<"Bust: Dealer's total exceeds 21"<<endl;
                break;
            }
        }

        //if the dealer has not bust, update the total points for the dealer
        dealer.setTotal(currCard);
        cout<<"The dealer's current points are "<<dealer.getTotal()<<endl;
        currentDealerTotal = dealer.getTotal();
    }
    return cardToDrawAtPos;
}

/** checks to see if the first two cards drawn by the player are the same
@return 1: the cards are the same
        0: card are not the same
@param Card: the first card drawn by the player
@param Card: the second card drawn by the player
*/
int Game::checkForSamePlayerCards(Card firstCard, Card secondCard)
{
    //check if the first two cards are aces from any suite
    if(firstCard.isAce()==1 && secondCard.isAce()==1)
        return 1;

    //check if the first two cards are both picture (King, Queen, Jack) cards
    else if(firstCard.isFaceCard()==1 && secondCard.isFaceCard()==1)
    {
        //check if they have the same picture
        if(firstCard.getCardType()==secondCard.getCardType())
            return 1;
    }
    //if they are neither aces not picture cards, they must have the same points to qualify as similar cards
    else if(firstCard.isFaceCard()==0 && secondCard.isFaceCard()==0)
    {
        if(firstCard.getPoints()==secondCard.getPoints())
            return 1;
    }
    return 0;
}


/**this function is called at the very beginning
@return void
@param
*/
void Game::playInitialHand()
{
    //the horizontal offset to draw a player's cards on the screen
    int horzOffPlayerCard = 25;

    //the loop runs as long as the player does not choose to stop playing or runs out of funds
    while(continuePlaying=='y')
    {
        //create a new deck of cards at the start of every new bet by the player
        DeckOfCards doc;

        //get the amount bet by the player
        getPlayerBet();

        //draw a simple image
        if(graphicsOn==1)
            drawTable();

        //variable to keep track of the position in the deck of cards from where the next
        //card will be drawn. Its is incremented by 1 every time a card is drawn to signify
        //that the card is removed from the deck of cards and no longer available
        int cardToDrawAtPos = 0;

        //card objects denoting the first 4 cards drawn
        Card currCard, dealerFirstCard, dealerSecondCard, playerFirstCard, playerSecondCard;

        //card hands of the player. The player always has one hand by default
        //if he chooses to split (under splitting condition), he has two hands
        Hand playerFirstHand, playerSecondHand;

        dealerFirstCard = dealer.drawCardAtPos(doc, cardToDrawAtPos++);
        dealer.setTotal(dealerFirstCard);
        dealerFirstCard.drawCard(1,0,1,"Dealer",graphicsOn);

        playerFirstCard = dealer.drawCardAtPos(doc, cardToDrawAtPos++);
        playerFirstHand = player.getFirstHand();
        playerFirstHand.setTotal(playerFirstCard);
        playerFirstCard.drawCard(horzOffPlayerCard,0,0,"Player",graphicsOn);

        dealerSecondCard = dealer.drawCardAtPos(doc, cardToDrawAtPos++);
        dealer.setTotal(dealerSecondCard);
        dealerSecondCard.drawCard(1,0,0,"Dealer",graphicsOn);

        playerSecondCard = dealer.drawCardAtPos(doc, cardToDrawAtPos++);
        playerSecondCard.drawCard(horzOffPlayerCard,0,0,"Player",graphicsOn);

        //check to see if the player has drawn two similar cards
        if(checkForSamePlayerCards(playerFirstCard, playerSecondCard)==1)
        {
            //variable to keep track of user's choice to split or not
            char splitHand = 'n';
            cout<<"Do you want to split the Cards? Enter 'y' for yes and any other key for no"<<endl;
            cin>>splitHand;

            //if the player chooses to split
            if(splitHand=='y')
            {
                //bet an equal amount on the second hand. The player has
                //effectively doubled his bet
                player.updateCurrentBet(playerBet);

                //
                playerSecondHand = player.getSecondHand();
                playerSecondHand.setValid(1);

                //update the total of the second hand with the points of the second card
                playerSecondHand.setTotal(playerSecondCard);

                cout<<endl;
                cout<<endl;
                cout<<"Playing the first (split) hand"<<endl;

                //calculate the total points for the first hand
                cardToDrawAtPos = calculatePlayerHandTotal(player, playerFirstHand, cardToDrawAtPos, doc,1);
                cout<<endl;
                cout<<endl;
                cout<<"Playing the second (split) hand"<<endl;

                //calculate the total points for the second hand
                cardToDrawAtPos = calculatePlayerHandTotal(player, playerSecondHand, cardToDrawAtPos, doc,2);

                //if at least one hand has not bust, draw cards for the dealer and
                //check to see if any hand wins against the dealer
                if(playerFirstHand.getBust()==0 || playerSecondHand.getBust()==0)
                {
                    cardToDrawAtPos = calculateDealerTotal(dealer, cardToDrawAtPos, doc);
                    if(playerFirstHand.getBust()==0 && playerSecondHand.getBust()!=0)
                    {
                        checkConditions(player, playerFirstHand, dealer,1);
                    }
                    else if(playerFirstHand.getBust()!=0 && playerSecondHand.getBust()==0)
                    {
                        checkConditions(player, playerSecondHand, dealer, 2);
                    }
                    else
                    {
                        checkConditions(player, playerFirstHand, dealer, 1);
                        checkConditions(player, playerSecondHand, dealer, 2);
                    }

                }
            }
            //if the player does not chose to split, play it as a regular (single) hand
            else
            {
                cardToDrawAtPos = playSingleGame(player, playerFirstHand, doc, playerSecondCard, dealerFirstCard, dealerSecondCard, cardToDrawAtPos);
            }
        }
        else
        {
            cardToDrawAtPos = playSingleGame(player, playerFirstHand, doc, playerSecondCard, dealerFirstCard, dealerSecondCard, cardToDrawAtPos);
        }

        //ask the player if they want to quit or continue playing
        if(continueGame() == 1)
        {
            //if player chooses to continue, reset all parameters so that a new game
            //may start
            reinitializeGame(player, dealer);
            continue;
        }
        else
            break;
    }
    int remainingChips = player.getRemainingChips() -player.getTotalChips();
    if(remainingChips > 0)
        cout<<"You are leaving the game after winning "<<remainingChips<<" chips"<<endl;
    else
        cout<<"You are leaving the game after losing "<<-remainingChips<<" chips"<<endl;
}

/**this function is called when either the first two cards for the player are dissimilar or
when the player chooses not to split cards
@return the position in the deck of cards from where the next card is to be drawn
@param Player&: a reference to the player object. passed as a reference in order to reflect the changes
       made to the object
@param Hand&: a reference to the object representing the current hand being played by the player
@param DeckOfCads: the deck of cards from which the cards will be drawn
@param Card: the player's first card
@param Card: the player's second card
@param Card: the dealer's first card
@param Card: the dealer's second card
@param cardToDrawAtPos: the postion from where cards need to be drawn for the deck of cards
*/
int Game::playSingleGame(Player& player, Hand& playerFirstHand, DeckOfCards doc, Card playerSecondCard, Card dealerFirstCard, Card dealerSecondCard, int cardToDrawAtPos)
{
    //if the second card drawn by the player is an ace, give the player
    //the option to set points for the card
    if(playerSecondCard.isAce()==1)
    {
        int aceValue = getAceChoice();
        playerSecondCard.setPoints(aceValue);
    }

    //update the points accumulated by the player's current hand after drawing the first two cards
    playerFirstHand.setTotal(playerSecondCard);

    //if this total exceeds 21, the player busts for the current hand
    if(playerFirstHand.getTotal()>21)
    {
        cout<<"Bust: your total exceeds 21"<<endl;
        //set the bust flag for the hand
        playerFirstHand.setBust(1);
        cout<<"The player loses "<<playerBet<<" chips"<<endl;
        //update the total chips of the player with this loss
        player.updateRemainingChips(-playerBet);
    }
    else
    {
        //check to see if either the player or the dealer has accumulated 21 points
        int result = checkInitialHand(player, playerFirstHand, dealerFirstCard, dealerSecondCard);
        if(result==0)
        {
            //if neither the player or dealer has a blackjack, draw cards for the player and update points
            cardToDrawAtPos = calculatePlayerHandTotal(player, playerFirstHand, cardToDrawAtPos, doc, 3);

            //if the player does not bust for the chosen hand
            if(playerFirstHand.getBust()==0)
            {
                //calculate the dealer's total points
                cardToDrawAtPos = calculateDealerTotal(dealer, cardToDrawAtPos, doc);
                //check to see who wins
                checkConditions(player, playerFirstHand, dealer, 3);
            }
        }
    }
    return cardToDrawAtPos;
}

/**this function checks to see if either the player and the dealer have 21 points after drawing
*the first 4 cards (two for the player and two for the dealer)
@return 1: if either the player or dealer has 21 points
        0: neither has 21 points
@param Player&; reference to the player object
@param Hand: the hand object representing the hand the player is currently playing
@param Card: the first card drawn by the dealer
@param Card: the second card drawn by the dealer
*/
int Game::checkInitialHand(Player& player, Hand playerHand, Card dealerFirstCard, Card dealerSecondCard)
{
    cout<<"the player's total points are: "<<playerHand.getTotal()<<endl;

    //check to see if the player already has a Blackjack after drawing the first two cards
    if(playerHand.getTotal()==21)
    {
        cout<<"Player has Blackjack. Player wins "<<playerBet<<" chips"<<endl;
        //the player wins. update his winnings
        player.updateRemainingChips(playerBet);
        return 1;
    }
    //if the player has less than 21 points and the second card drawn by the
    //dealer has 10 points
    if(playerHand.getTotal()<=21 && dealerSecondCard.getPoints()>=10)
    {
        int currPlayerTotal = playerHand.getTotal();
        //check if the dealer has a blackjack
        int flag = checkForDealerBlackjack(dealerFirstCard,dealerSecondCard);

        //if the player does not have a blackjack and the dealer does,
        //the player loses. update his remaining chips with the loss
        if(currPlayerTotal<21 && flag==1)
        {
            cout<<"Player loses "<<playerBet<<" chips"<<endl;
            player.updateRemainingChips(-playerBet);
            return 1;
        }
        else if(currPlayerTotal==21 && flag==1)
        {
            cout<<"player and dealer both have 21 points. Nothing won or lost by the player"<<endl;
            return 1;
        }
    }
    return 0;
}

/**check to see who has the greater points between the player and the dealer.
@return void
@param Player&: reference to the player object
@param Hand: the hand object representing the hand being played by the player
@param Dealer: the dealer object
@param gameNum: 1: represents the first split hand for the player
                2: represents the second split hand for the player
                3: represents the situation where either the player does not
                chose to split or the situation for splitting has not arisen
*/
void Game::checkConditions(Player& player, Hand playerHand, Dealer dealer, int gameNum)
{
    //get the players total accumulated points
    int finalPlayerTotal = playerHand.getTotal();

    //get the dealers total accumulated points
    int finalDealerTotal = dealer.getTotal();

    //if the dealer has not bust, check to see who has the greater points
    if(dealer.getBust()==0)
    {
        //dealer wins
        if(finalDealerTotal>finalPlayerTotal)
        {
            if(gameNum==3)
            {
                cout<<"The player loses "<<playerBet<<" chips"<<endl;
                player.updateRemainingChips(-playerBet);
            }
            else
            {
                cout<<"The player loses "<<playerBet<<" chips on "<<gameNum<<" hand"<<endl;
                player.updateRemainingChips(-playerBet);
            }
        }
        //player wins
        else if(finalDealerTotal<finalPlayerTotal)
        {
            if(gameNum==3)
            {
                cout<<"The player wins "<<playerBet<<" chips"<<endl;
                player.updateRemainingChips(playerBet);
            }
            else
            {
                cout<<"The player wins "<<playerBet<<" chips on "<<gameNum<<" hand"<<endl;
                player.updateRemainingChips(playerBet);
            }
        }
        //both dealer and player have the same number of points
        else
        {
            if(gameNum!=3)
                cout<<"Dealer and Player have equal points on "<<gameNum<<" hand. Player neither wins nor loses any chips"<<endl;
            else
                cout<<"Dealer and Player have equal points. Player neither wins nor loses any chips"<<endl;
        }
    }
    //dealer has bust. the player wins
    else
    {
        if(playerHand.getBust()==0)
            player.updateRemainingChips(playerBet);
        if(gameNum!=3)
            cout<<"Because dealer busts, the player wins "<<playerBet<<" chips on "<<gameNum<<" hand"<<endl;
        else
            cout<<"Because dealer busts, the player wins "<<playerBet<<" chips"<<endl;
    }
}

/**function reinitializes the player and dealer so that a new game may be played
@return void
@param Player&: reference to the player object
@param Dealer&: reference to the dealer object
*/
void Game::reinitializeGame(Player& player, Dealer& dealer)
{
    player.reintialize();
    dealer.reintialize();
}

/**function draws a basic structure which demarcates the console
into areas where the dealer and player cards will be drawn
@return
@param
*/
void Game::drawTable()
{
    string border="-";
    for(int i=0;i<34;i++)
    {
        border+="-";
    }
    cout<<border<<endl;
    cout<<"|     DEALER     |     PLAYER     |"<<endl;
    cout<<border<<endl;

}

/**
call to function main
*/
int main()
{
    //variable to store user's choice to switch graphics on/off
    int graphics;
    cout<<"Do you want to display basic graphical images of the cards?"<<endl;
    cout<<"Enter 1 to switch on graphics and 0 to switch off"<<endl;
    cin>>graphics;

    while(1)
    {
        //only accept numeric input
        if(!cin)
        {
            cin.clear();
            cin.ignore();
            cout<<"Please enter a numeric input (0 or 1) only"<<endl;
            cin>>graphics;
        }

        //only valid choices are a 0 and a 1
        else if(graphics == 1 || graphics == 0)
        {
            break;
        }
        else
        {
            cout<<"Please chose 0 or 1 only"<<endl;
            cin>>graphics;
        }
    }

    //create a game object which will play the game of Blackjack
    Game game;
    //set the user's graphical preferences
    game.setGraphics(graphics);
    game.playInitialHand();
}
