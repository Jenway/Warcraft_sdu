#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../include/Enums.h"
#include "GameFrame.h"
#include <QCloseEvent>
#include <QEvent>
#include <QFrame>
#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    int step_count = 0;

    void rungame(inputData data);

private:
    std::vector<inputData> datas;
    Ui::MainWindow* ui;
    QPainter* painter;
    GameFrame* gameFrame;
    void getInput();

protected:

    void closeEvent(QCloseEvent*);
private slots:
    void on_gameStartButton_clicked();
    void on_defaultData_clicked();
};
#endif // MAINWINDOW_H
