/**
    Player.cpp
    Purpose: Represents a player.

    @author Vikramjit Sandhu
*/

#include "Player.h"

Player::Player()
{
    totalChips = TOTAL_PLAYER_CHIPS;
    remainingChips = totalChips;
    currentBet = 0;
    hands[0].setValid(1);
}

void Player::reintialize()
{
    currentBet = 0;
    hands[0].reintialize();
    hands[1].reintialize();
}
