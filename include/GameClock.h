#if !defined(GAMECLOCK_H)
#define GAMECLOCK_H

class GameClock {

private:
    int hours = 0;
    int minutes = 0;
    int endTime = 0;

public:
    int getHours() { return hours; }
    int getMinutes() { return minutes; }
    bool isEnd()
    {
        return hours * 60 + minutes > endTime;
    }
    void update()
    {
        minutes += 5;
        if (minutes == 60) {
            hours++;
            minutes = 0;
        }
    }
    GameClock() = delete;
    GameClock(int endtime)
        : endTime(endtime)
    {
    }
};
#endif