Blackjack
=========
This project Blackjack.cbp has been developed on thw Windows 7 platform on CodeBlocks IDE. It simulates a game of 
Blackjack, with the following features:

Hit: Allows the player to ask for an additional card
Stand: Informs the dealer that no more cards need to be dealt
Split: If the player received two cards of the same suite, allows the player to split them.

I have not implemented the following features:

Insurance
Double down

To reiterate,only the actions to hit, stand and splitting are implemented and the game involves one dealer and one 
player only. I have used the following websites for understanding the rules of Blackjack:

http://zone.msn.com/gameplayer/gameplayer.aspx?game=blackjack&instance=default
http://en.wikipedia.org/wiki/Blackjack


NOTE: The player is allowed to bet 1 or 5 or 10 chips at a time only


The rules have been described in detail below:


This document explains the rules implemented by the author (Vikramjit Sandhu) for the game of Blackjack:
Rules for Blackjack game (Only single deck used for playing the game):

1. The game starts with dealing 4 cards, 2 for the dealer, 2 for the player. After dealing each card the game informs the 
   player and the dealer of the type of card (number and suite) dealt.
	 
	 1a: First card goes to the dealer. Since it is a face down card, it is depcited as an unknown card.
	 1b: Second card goes to the player.
	 1c: Third card goes to the dealer.
	 1d: Fourth card goes to the player.

2. If the first card received by the player is an ace of any suite, it is always given 11 points.

3. If the player receives any other card as an ace, they are given the option to set it as 1 or 11 points.
	 
	 3a: If the player is dealt an ace and setting the value as 11 points would lead to the total points for the player 
	 exceeding 21, the card is automatically allocated 1 point.
	 3b: Once the points for an ace have been set, they may not be set again.

4. After dealing the first 4 cards, the game checks to see if the player has a blackjack, i.e 21 points. If yes the player
   wins an amount equal to the number of chips bet and the player is given the option to continue or quit. If the player 
   chooses to continue, the entire process is repated.

5. If the player does not have a blackjack and the second card received by the dealer has a value of greater than 10 
   points, then the first card for the dealer is examined to see if dealer had a blackjack. If yes, the player loses his
   bet and is again given the option to continue or quit playing. If the player does not have a black jack, the player is 
   informed as such but is not told what is the face down card for the dealer.

6. If both the player and dealer do not have a blackjack, the player is then given the option to hit or stand. The player 
   id dealt card  till either he decides to stand, or his total exceeds 21 (bust). If the player busts, he loses his bet 
   irrespective of the dealer's  total.

7. Once the player decides to stand (and no bust for the player), the unknown card for the dealer is revealed and the 
   dealer's total  calculated. If the dealer's total is greater than the player's total, then the player loses and is 
   given the option to quit or continue. If the dealer's total is less than the player's total, the dealer is dealt cars 
   untill their total is 17 or greater. If the dealer's total ends up being greater than 21, the dealer busts and the 
   player wins irrespective of their total accumulated points.
   
	 7a: when the delaer is draws cards and is dealt an ace, the value of the ace is always set to 11, unless setting it to 
	 11 results in the the dealer's total exceeding 11, in which case the card's pomts are set to 1. The dealer cannot 
	 explicitly choose to set the card's points.

SPLITTING:

1. If the first two cards received by the player are the same, the player is given the choice to split the cards into 2 
   hands. If he chooses not to, the game continues as a regular game. If he chooses to split, then the game continues as 
   two hands. The game automatically bets an equal amount on the second game. E.g. if the player makes an initial bet of 
   x chips, then after splitting the player has bet an amount of x chips on each game. The points for each hand are 
   calculated individually. First, one hand is completely played out by dealing cards till player stands or busts. If the 
   player busts on the hand, then he loses the maount best straight away. Next the second hand is played in a similar 
   fashion. After this the dealer is dealt carsd till bust or till dealedr pints exceed 17.
   
	 1a: When splitting aces, they are always allocated 11 	points. Subsequent aces may be given poibts chosen 	by the 
	 player.
	 1b: When player splits,  and the second card dealt to 	the dealer has more than 11 points, the dealer does NOT check 
	 for blackjack untill player stands or busts.
