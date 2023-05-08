#include "../include//GameClock.h"

int GameClock::end = 0;

bool GameClock::isEnd()
{
    return hours * 60 + minutes >= end;
}
