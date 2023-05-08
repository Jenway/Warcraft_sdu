#if !defined(GAMECLOCK_H)
#define GAMECLOCK_H

class GameClock {

private:
    int hours = 0;
    int minutes = 0;

public:
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    void update()
    {
        minutes++;
        if (minutes == 60) {
            hours++;
            minutes = 0;
        }
    }
};
#endif