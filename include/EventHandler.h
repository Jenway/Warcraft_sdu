#if !defined(EVENTHANDLER_H)
#define EVENTHANDLER_H

#include <memory>

#include "GameClock.h"
#include "Headquarter.h"

class EventHandler {
private:
    std::shared_ptr<Headquarter> HQ;
    void logEvent(int hours);
    void spawnWarrior();
    void lionEscape();
    void warriorsMarch();
    void wolfSnatch();
    void reportBattle();
    void warriorYell();
    void reportLife();
    void reportWeapon();

public:
    bool onClockUpdate(GameClock& clock);
    EventHandler() = delete;
    EventHandler(std::shared_ptr<Headquarter> HQ)
        : HQ(HQ)
    {
    }
};

#endif // EVENTHANDLER_H