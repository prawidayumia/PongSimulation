#include "Player.h" 

const char* Player::setPlayerName(Players player)
{
    switch (player) {
    case PlayerX:
        return "Player X ";
        break;
    case PlayerY:
        return "Player Y ";
        break;
    };
}

void Player::setHit(float hit)
{
    this->hit = hit;
}

float Player::getHit()
{
    return hit;
}
