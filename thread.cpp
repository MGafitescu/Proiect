#include "thread.h"
#include <string.h>


thData::thData(int idThread, int cl, char username[20])
{
    this->idThread = idThread;
    this->cl = cl;
    strcpy(this->username,username);
}

thData::thData(thData *ptr)
{
    this->idThread = ptr->idThread;
    this->cl = ptr->cl;
    strcpy(this->username,ptr->username);
}

void thData::setUsername(char username[20])
{
    strcpy(this->username,username);
}