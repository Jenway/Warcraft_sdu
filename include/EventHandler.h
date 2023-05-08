#if !defined(EVENTHANDLER_H)
#define EVENTHANDLER_H

#include <memory>

#include "GameClock.h"
#include "Headquarter.h"

class EventHandler {
private:
    std::shared_ptr<Headquarter> redHQ;
    std::shared_ptr<Headquarter> blueHQ;
    std::shared_ptr<GameClock> clock;
    void logEvent(int hours);
    void spawnWarrior();
    void lionEscape();
    void warriorsMarch();
    void wolfSnatch();
    void reportBattle();
    void warriorYell();
    void reportLife();
    void reportWeapon(int hour, int minute);

public:
    void setClock(std::shared_ptr<GameClock> clock);
    bool onClockUpdate();
    bool isGameOver();
    EventHandler() = delete;
    EventHandler(std::shared_ptr<Headquarter> redHQ, std::shared_ptr<Headquarter> blueHQ)
        : redHQ(redHQ)
        , blueHQ(blueHQ)
    {
    }
};

#endif // EVENTHANDLER_H