#if !defined(EVENTHANDLER_H)
#define EVENTHANDLER_H

#include <memory>

#include "GameClock.h"
#include "Headquarter.h"

class EventHandler {
private:
    std::shared_ptr<Headquarter> redHQ;
    std::shared_ptr<Headquarter> blueHQ;

    std::vector<std::shared_ptr<City>> cities;
    std::shared_ptr<GameClock> clock;

    void spawnWarrior();
    void lionEscape();
    void warriorsMarch();
    void wolfSnatch();

    void reportLife();
    void reportWeapon();
    void battle();
    void reportBattle();
    void afterBattle();

public:
    void setClock(std::shared_ptr<GameClock> clock);
    void setCities(std::vector<std::shared_ptr<City>> cities);
    void onClockUpdate();
    bool isGameOver();
    EventHandler() = delete;
    EventHandler(std::shared_ptr<Headquarter> redHQ, std::shared_ptr<Headquarter> blueHQ)
        : redHQ(redHQ)
        , blueHQ(blueHQ)
    {
    }
};

#endif // EVENTHANDLER_H