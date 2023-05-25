#include "gameframe.h"
#include "include/Enums.h"
#include "ui_gameframe.h"
#include <QFrame>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <qpixmap.h>
#include <sstream>
#include <vector>

GameFrame::GameFrame(QWidget* parent)
    : QFrame(parent)
    , ui(new Ui::GameFrame)
{
    ui->setupUi(this);
}

GameFrame::~GameFrame()
{
    delete ui;
}

void GameFrame::updateFrame(std::vector<updateData> data)
{
    this->m_data = data;
}

void GameFrame::showAnime()
{
    // 清空画布
    this->update();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updataAnime()));
    // 设置定时器每个多少毫秒更新一次
    timer->start(300);
}

void GameFrame::updataAnime()
{
    this_data = this->m_data[frame];

    frame++;
    if (frame == this->m_data.size()) {
        frame = 0;
        timer->stop();
    }
    this->update();
    qDebug() << "updataAnime";
}

void GameFrame::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    // 画个 五角星
    painter.drawPolygon(QPolygonF(
        QVector<QPointF> {
            QPointF(0, 85.5), QPointF(75, 75),
            QPointF(100, 10), QPointF(125, 75),
            QPointF(200, 85.5), QPointF(150, 125),
            QPointF(160, 190), QPointF(100, 150),
            QPointF(40, 190), QPointF(50, 125),
            QPointF(0, 85.5) }));

    // 在五角星右侧绘制 一个bridge
    // 打开图片
    QPixmap bridgePixmap(":/images/Resources/bridge.png");
    // 调整图片大小
    bridgePixmap = bridgePixmap.scaled(100, 100, Qt::KeepAspectRatio);
    // 绘制图片
    painter.drawPixmap(200 + bridgeFrame * 60, 90, bridgePixmap);
    this->bridgeFrame = (this->bridgeFrame + 1) % 7;

    // 绘制背景
    // 开摆了开摆了，累死了喵..
    if (this->m_data.size() == 0) {
        QPixmap redHeadquarterPixmap(":/images/Resources/planetred.png");
        // 调整图片大小
        redHeadquarterPixmap = redHeadquarterPixmap.scaled(100, 100, Qt::KeepAspectRatio);
        // 绘制图片
        painter.drawPixmap(0, this->height() / 3, redHeadquarterPixmap);
        for (int i = 0; i < 7; i++) {
            // 绘制城市
            // 打开图片
            QPixmap cityPixmap(":/images/Resources/bridge.png");
            // 调整图片大小
            cityPixmap = cityPixmap.scaled(100, 100, Qt::KeepAspectRatio);
            // 绘制图片
            painter.drawPixmap(100 + i * 100, this->height() / 3 + 100, cityPixmap);
        }
        QPixmap blueHeadquarterPixmap(":/images/Resources/planetblue.png");
        // 调整图片大小
        blueHeadquarterPixmap = blueHeadquarterPixmap.scaled(100, 100, Qt::KeepAspectRatio);
        // 绘制图片
        painter.drawPixmap(this->width() - 100, this->height() / 3, blueHeadquarterPixmap);

        // 绘制 武士
        for (int i = 0; i < 7; i++) {
            // 绘制城市
            // 打开图片
            QPixmap warriorPixmap(":/images/Resources/wolf.png");
            // 调整图片大小
            warriorPixmap = warriorPixmap.scaled(50, 50, Qt::KeepAspectRatio);
            // 绘制图片
            painter.drawPixmap(100 + i * 100, this->height() / 3 + 100, warriorPixmap);
        }
        for (int i = 0; i < 7; i++) {
            // 绘制城市
            // 打开图片
            QPixmap warriorPixmap(":/images/Resources/dragon.png");
            // 调整图片大小
            warriorPixmap = warriorPixmap.scaled(50, 50, Qt::KeepAspectRatio);
            // 图片水平翻转
            warriorPixmap = warriorPixmap.transformed(QTransform().scale(-1, 1));
            // 绘制图片
            painter.drawPixmap(100 + i * 100 + 50, this->height() / 3 + 100, warriorPixmap);
        }
    } else {
        QPixmap redHeadquarterPixmap(":/images/Resources/planetred.png");
        // 调整图片大小
        redHeadquarterPixmap = redHeadquarterPixmap.scaled(100, 100, Qt::KeepAspectRatio);
        // 绘制图片
        painter.drawPixmap(0, this->height() / 3, redHeadquarterPixmap);
        for (int i = 0; i < this->this_data.cityNumber; i++) {
            // 绘制城市
            // 打开图片
            QPixmap cityPixmap(":/images/Resources/bridge.png");
            // 调整图片大小
            cityPixmap = cityPixmap.scaled(100, 100, Qt::KeepAspectRatio);
            // 绘制图片
            painter.drawPixmap(100 + i * 100, this->height() / 3 + 100, cityPixmap);
        }
        QPixmap blueHeadquarterPixmap(":/images/Resources/planetblue.png");
        // 调整图片大小
        blueHeadquarterPixmap = blueHeadquarterPixmap.scaled(100, 100, Qt::KeepAspectRatio);
        // 绘制图片
        painter.drawPixmap(this->width() - 100, this->height() / 3, blueHeadquarterPixmap);

        // 绘制 武士
        for (int i = 0; i < this->this_data.cityNumber; i++) {
            // 绘制城市
            // 打开图片
            if (this_data.redWarrior.size() > i) {
                WarriorType redType = this->this_data.redWarrior[i];
                QPixmap redwarriorPixmap;
                if (redType == WarriorType::dragon) {
                    redwarriorPixmap = QPixmap(":/images/Resources/dragon.png");
                } else if (redType == WarriorType::iceman) {
                    redwarriorPixmap = QPixmap(":/images/Resources/iceman.png");
                } else if (redType == WarriorType::lion) {
                    redwarriorPixmap = QPixmap(":/images/Resources/lion.png");

                } else if (redType == WarriorType::ninja) {
                    redwarriorPixmap = QPixmap(":/images/Resources/ninja.png");
                } else if (redType == WarriorType::wolf) {
                    redwarriorPixmap = QPixmap(":/images/Resources/wolf.png");
                } else {
                } // 调整图片大小
                redwarriorPixmap = redwarriorPixmap.scaled(50, 50, Qt::KeepAspectRatio);

                // 绘制图片
                painter.drawPixmap(100 + i * 100, this->height() / 3 + 100, redwarriorPixmap);
            }
            if (this_data.blueWarrior.size() > i) {

                WarriorType blueType = this->this_data.blueWarrior[i];
                QPixmap bluewarriorPixmap;
                if (blueType == WarriorType::dragon) {
                    bluewarriorPixmap = QPixmap(":/images/Resources/dragon.png");
                } else if (blueType == WarriorType::iceman) {
                    bluewarriorPixmap = QPixmap(":/images/Resources/iceman.png");
                } else if (blueType == WarriorType::lion) {
                    bluewarriorPixmap = QPixmap(":/images/Resources/lion.png");

                } else if (blueType == WarriorType::ninja) {
                    bluewarriorPixmap = QPixmap(":/images/Resources/ninja.png");
                } else if (blueType == WarriorType::wolf) {
                    bluewarriorPixmap = QPixmap(":/images/Resources/wolf.png");
                } else {
                }
                bluewarriorPixmap = bluewarriorPixmap.scaled(50, 50, Qt::KeepAspectRatio);
                // 蓝色水平翻转
                bluewarriorPixmap = bluewarriorPixmap.transformed(QTransform().scale(-1, 1));
                painter.drawPixmap(100 + i * 100 + 50, this->height() / 3 + 100, bluewarriorPixmap);
            }
        }
    }
}
