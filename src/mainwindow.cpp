#include "mainwindow.h"
#include "../include/Enums.h"
#include "../include/Game.h"
#include "../include/GameIO.h"
#include "GameFrame.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QTextStream>
#include <iostream>
#include <memory>
#include <qdebug.h>
#include <qframe.h>
#include <qlabel.h>
#include <qpainter.h>
#include <vector>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Warcraft SDU @Jenway");
    this->setWindowIcon(QIcon(":images/Resources/bokiChan_icon.png"));
    gameFrame = new GameFrame(this);
    gameFrame->setFixedSize(this->size().width() * 2 / 3, this->size().height() * 2 / 3);
    gameFrame->move(0, this->size().height() - gameFrame->height());
    gameIO::setOutputCallback([&](const std::string& msg) {
        this->ui->textBrowser->insertPlainText(msg.c_str());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rungame(inputData data)
{
    std::unique_ptr<Game> game = std::make_unique<Game>(data, this);
    std::vector<updateData> updateDatas = game->run();
    this->gameFrame->updateFrame(updateDatas);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMessageBox msg;
    QString wintitle = QString("要结束游戏吗\n");
    msg.setWindowTitle(wintitle);
    msg.setText("游戏会结束~");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int result = msg.exec();

    if (result == QMessageBox::Yes) {
        // 结束游戏，退出应用程序
        QApplication::quit();
    } else {
        // 取消关闭事件， 阻止窗口关闭
        event->ignore();
    }
}

void MainWindow::on_gameStartButton_clicked()
{
    // 清空 datas
    datas.clear();
    // 读取输入
    getInput();
    if (datas.empty()) {
        QMessageBox::warning(this, "警告", "输入为空");
        return;
    }
    // 清空文本框
    this->ui->textBrowser->clear();
    // 清空 output.txt
    std::ofstream ofs("output.txt", std::ios::trunc);
    ofs.close();

    for (auto& data : datas) {
        rungame(data);
    }
    gameFrame->showAnime();
}

void MainWindow::on_defaultData_clicked()
{
    this->ui->textInput->insertPlainText(
        "4\n500 6 100 6000\n20 20 30 10 20\n5 5 5 5 5\n1000 15 100 5430\n20 20 30 10 20\n5 5 5 5 5\n50 6 100 600\n20 20 30 10 20\n5 5 5 5 5\n1000 6 100 6000\n20 20 30 10 20\n5 5 5 5 5\n");
}

void MainWindow::getInput()
{
    QString inputText = this->ui->textInput->toPlainText();
    QTextStream inStream(&inputText);
    // 第一行是 game_round ，也即 局数
    int game_round = inStream.readLine().toInt();
    // qDebug() << game_round;
    for (int i = 0; i < game_round; i++) {
        inputData data;
        data.game_round = i + 1;
        // 第二行是 M N K T
        QString line = inStream.readLine();
        QStringList list = line.split(" ");
        data.M = list[0].toInt();
        data.N = list[1].toInt();
        data.K = list[2].toInt();
        data.T = list[3].toInt();
        // qDebug() << data.M << data.N << data.K << data.T;
        // 第三行是默认生命值
        line = inStream.readLine();
        list = line.split(" ");
        for (int i = 0; i < 5; i++) {
            data.default_lives[i] = list[i].toInt();
        }
        // qDebug() << data.default_lives;
        // 第四行是默认攻击力
        line = inStream.readLine();
        list = line.split(" ");
        for (int i = 0; i < 5; i++) {
            data.default_attacks[i] = list[i].toInt();
        }
        // qDebug() << data.default_attacks;
        datas.emplace_back(data);
    }
}
