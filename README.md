# 期末大作业 `魔兽争霸`

## 说明

这是 SDU 计科专业 2022 级 `高级程序语言设计` 课程的大作业，以 old school 游戏魔兽争霸为背景。

代码托管在 [Github](https://github.com/Jenway/Warcraft_sdu)上。

## 使用

暂定只通过控制台进行输入输出

## 编译

## 结构介绍

### include\Warrior.h && src\Warrior.cpp

抽象 `Warrior` ,战士类

包含属性如下:

- m_life 生命值
- m_number 战士

派生出 `dragon` 、`ninja`、`iceman`、`lion`、`wolf`、五种战士类

包含属性:

- default_life 每个战士都设置的单独的静态变量，储存其默认生命值

### include\Headquarter.h && src\Headquater.cpp

抽象 `Headquarter` 司令部类

## 收获与感想

配置 cmake比上次写 (已经鸽掉的) 小恐龙有了些许进步。嘛，可能是因为还没用第三方库的原因。

设计模式，`chatgpt` 告诉我工厂模式这种设计模式，让我不禁感慨自己知识的匮乏，看来，不只需要学习语言特性与轮子，还需要学习设计模式等等。

> warning C4819: 该文件包含不能在当前代码页(936)中表示的字符。请将该文件保存为 Unicode 格式以防止数据丢失

`add_compile_options("$<$[C_COMPILER_ID:MSVC](C_COMPILER_ID:MSVC):/source-charset:utf-8>")`
