#include "src/mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>
#include <iostream>
#include <qapplication.h>
#include <qcommandlineparser.h>
#include <qcoreapplication.h>

void commandLineInterface(QApplication& a);

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    commandLineInterface(a);
    MainWindow w;
    w.show();
    return a.exec();
}

void commandLineInterface(QApplication& a)
{
    // 设置应用程序的名称和版本号
    QCoreApplication::setApplicationName("Warcraft SDU");
    QCoreApplication::setApplicationVersion("1.0");
    QCommandLineParser parser;
    // 添加对应的版本配置
    parser.addVersionOption();
    parser.process(a);
}