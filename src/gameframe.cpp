#include "GameFrame.h"
#include "../include/Enums.h"
#include "ui_gameframe.h"
#include <QFrame>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <iomanip>
#include <qpixmap.h>
#include <sstream>
#include <vector>

GameFrame::GameFrame(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::GameFrame)
{
    ui->setupUi(this);
    label = new QLabel(this);
    // label->setAttribute(Qt::WA_OpaquePaintEvent);
    label->setGeometry(680, 90, 100, 100);
    // 设置字体
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    font.setFamily("Microsoft YaHei");
    label->setFont(font);
    label->show();
    timer = new QTimer(this);
    timer->stop();
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
    // 重置 timer
    timer->stop();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnime()));
    // 设置定时器每个多少毫秒更新一次
    timer->start(300);
}

void GameFrame::updateAnime()
{
    this_data = this->m_data[frame];
    if (frame == this->m_data.size()) {
        frame = 0;
        timer->stop();
    }
    if (this_data.redTaken || this_data.blueTaken) {
        timer->stop();
        return;
    }
    frame++;

    this->update();
    // qDebug() << "updataAnime";
}

void GameFrame::paintEvent(QPaintEvent*)
{
    qDebug() << "paintEvent";
    // who the fuck func is calling this?

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
    // 桥能到达的最右边是 200 + 7 * 60 = 620
    // 在最右边画一个时钟 用 qlabel
    int hour = this_data.hour, minute = this_data.minute;
    // 设置内容
    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << hour << ':' << std::setw(2) << std::setfill('0') << minute << ' ';
    label->setText(QString::fromStdString(ss.str()));

    // 绘制背景
    // 开摆了开摆了，累死了喵..
    if (this->m_data.size() == 0) {
        QPixmap redHeadquarterPixmap(":/images/Resources/planetred.png");
        // 调整图片大小
        redHeadquarterPixmap = redHeadquarterPixmap.scaled(100, 100, Qt::KeepAspectRatio);
        // 绘制图片
        painter.drawPixmap(0, this->height() / 3, redHeadquarterPixmap);
        QPixmap redHQPixmap(":/images/Resources/redHQ1.png");
        // 调整图片大小
        redHQPixmap = redHQPixmap.scaled(100, 100, Qt::KeepAspectRatio);
        // 绘制图片
        painter.drawPixmap(0, this->height() / 3 + 100, redHQPixmap);
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

        QPixmap blueHQPixmap(":/images/Resources/blueHQ1.png");
        // 调整图片大小
        blueHQPixmap = blueHQPixmap.scaled(100, 100, Qt::KeepAspectRatio);
        // 绘制图片
        painter.drawPixmap(this->width() - 100, this->height() / 3 + 100, blueHQPixmap);
        // 绘制 武士
        for (int i = 0; i < 7; i++) {
            // 绘制城市
            // 打开图片
            bool isDraw = true;
            QPixmap warriorPixmap;
            if (i % 3 == 0) {
                warriorPixmap.load(":/images/Resources/dragon.png");
            } else if (i % 3 == 1) {
                warriorPixmap.load(":/images/Resources/ninja.png");
            } else {
                isDraw = false;
            }
            if (isDraw) {

                // warriorPixmap = QPixmap(":/images/Resources/wolf.png");
                // 调整图片大小
                warriorPixmap = warriorPixmap.scaled(50, 50, Qt::KeepAspectRatio);
                // 绘制图片
                painter.drawPixmap(100 + i * 100, this->height() / 3 + 100, warriorPixmap);
            }
        }
        for (int i = 0; i < 7; i++) {
            // 绘制城市
            // 打开图片
            QPixmap warriorPixmap;
            if (i % 3 == 0) {
                warriorPixmap.load(":/images/Resources/iceman.png");
            } else if (i % 3 == 1) {
                warriorPixmap.load(":/images/Resources/lion.png");
            } else {
                warriorPixmap.load(":/images/Resources/wolf.png");
            }
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
        // if red headquarter is taken, draw a blue flag
        if (this_data.redTaken) {
            QPixmap redHQPixmap(":/images/Resources/redHQ2.png");
            // 调整图片大小
            redHQPixmap = redHQPixmap.scaled(100, 100, Qt::KeepAspectRatio);
            // 绘制图片
            painter.drawPixmap(0, this->height() / 3 + 100, redHQPixmap);
        } else {

            QPixmap redHQPixmap(":/images/Resources/redHQ1.png");
            // 调整图片大小
            redHQPixmap = redHQPixmap.scaled(100, 100, Qt::KeepAspectRatio);
            // 绘制图片
            painter.drawPixmap(0, this->height() / 3 + 100, redHQPixmap);
        }

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

        if (this_data.blueTaken) {
            QPixmap blueHQPixmap(":/images/Resources/blueHQ2.png");
            // 调整图片大小
            blueHQPixmap = blueHQPixmap.scaled(100, 100, Qt::KeepAspectRatio);
            // 绘制图片
            painter.drawPixmap(this->width() - 100, this->height() / 3 + 100, blueHQPixmap);
        } else {

            QPixmap blueHQPixmap(":/images/Resources/blueHQ1.png");
            // 调整图片大小
            blueHQPixmap = blueHQPixmap.scaled(100, 100, Qt::KeepAspectRatio);
            // 绘制图片
            painter.drawPixmap(this->width() - 100, this->height() / 3 + 100, blueHQPixmap);
        }

        // 绘制 武士
        for (int i = 0; i < this->this_data.cityNumber; i++) {
            // 绘制城市
            // 打开图片
            if (this_data.redWarrior.size() > i) {
                WarriorType redType = this->this_data.redWarrior[i];
                QPixmap redwarriorPixmap;
                bool isDraw = true;
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
                    isDraw = false;
                } // 调整图片大小
                if (isDraw) {
                    redwarriorPixmap = redwarriorPixmap.scaled(50, 50, Qt::KeepAspectRatio);

                    // 绘制图片
                    painter.drawPixmap(100 + i * 100, this->height() / 3 + 100, redwarriorPixmap);
                }
            }
            if (this_data.blueWarrior.size() > i) {
                bool isDraw = true;
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
                    isDraw = false;
                }
                if (isDraw) {
                    bluewarriorPixmap = bluewarriorPixmap.scaled(50, 50, Qt::KeepAspectRatio);
                    // 蓝色水平翻转
                    bluewarriorPixmap = bluewarriorPixmap.transformed(QTransform().scale(-1, 1));
                    painter.drawPixmap(100 + i * 100 + 50, this->height() / 3 + 100, bluewarriorPixmap);
                }
            }
        }
    }
}
