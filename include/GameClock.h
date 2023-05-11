#if !defined(GAMECLOCK_H)
#define GAMECLOCK_H

class GameClock {

private:
    int hours = 0;
    int minutes = 0;
    static int end;

public:
    int getHours() { return hours; }
    int getMinutes() { return minutes; }
    static int getEnd() { return end; }
    static void setEndTime(int endtime) { end = endtime; }
    bool isEnd();
    void update()
    {
        minutes += 5;
        if (minutes == 60) {
            hours++;
            minutes = 5;
        }
    }
};
#endif