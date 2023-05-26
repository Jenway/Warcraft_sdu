#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include "../include/Enums.h"
#include <qlabel.h>
#include <qtmetamacros.h>
#include <qwindowdefs.h>
#include <vector>

namespace Ui {
class GameFrame;
}

class GameFrame : public QWidget {
    Q_OBJECT

public:
    explicit GameFrame(QWidget* parent = nullptr);
    ~GameFrame();
    void updateFrame(std::vector<updateData> data);
    void showAnime();

protected slots:
    void updateAnime();

private:
    Ui::GameFrame* ui;
    std::vector<updateData> m_data {};
    updateData this_data;
    QTimer* timer;
    QLabel* label;
    int frame = 0;
    int bridgeFrame = 0;

protected:
    void paintEvent(QPaintEvent*);
};

#endif // GAMEFRAME_H
