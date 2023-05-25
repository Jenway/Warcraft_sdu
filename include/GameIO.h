#include "include/Enums.h"
#if !defined(INPUTOUTPUT_H)
#define INPUTOUTPUT_H

#include <QDebug>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

class gameIO {
public:
    typedef std::function<void(const std::string&)> OutputCallback;
    static OutputCallback s_outputCb;
    static void setOutputCallback(const OutputCallback& cb)
    {
        s_outputCb = cb;
    }
    gameIO() = delete;
    ~gameIO() = delete;
    // static void getInput(std::vector<inputData>& datas)
    // {
    // }

    static void print(std::string str)
    {
        std::cout << str << std::endl;
        qDebug() << str.c_str();
        if (s_outputCb) {
            s_outputCb(str);
        }
        // 写入日志文件
        // 打开
        std::ofstream fout;
        fout.open("output.txt", std::ios::app);
        // 写入
        fout << str;
        // 关闭
        fout.close();
    }
};

#endif // INPUTOUTPUT_H