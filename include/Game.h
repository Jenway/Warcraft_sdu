#include "include/Enums.h"
#include <vector>
#if !defined(GAME_H)
#define GAME_H

#include "../src/mainwindow.h"
#include "City.h"
#include "Enums.h"
#include <QObject>
#include <memory>

class Game {

public:
    Game() = delete;
    Game(inputData data, MainWindow* w)
        : data(data)
        , w(w)
    {
    }
    ~Game() = default;
    std::vector<updateData> run();

private:
    MainWindow* w;
    inputData data;
    std::vector<std::shared_ptr<City>>* m_citys = nullptr;
    updateData getUpdateData();
};

#endif // GAME_H
