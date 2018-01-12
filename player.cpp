#include "player.h"
#include <string.h>

Player::Player(int id, char username[20])
{
    this->id=id;
    strcpy(this->username,username);
    this->punctaj=0;
}

char * Player::getUsername()
{
    return this->username;
}

void Player::setPunctaj(int punctaj)
{
     this->punctaj=punctaj;
}
    

int Player::getPunctaj()
{
    return this->punctaj;
}