# 2023年SDU高级程序设计期末大作业 `魔兽争霸`

## 说明

这是 SDU 计科专业 2022 级 `高级程序语言设计` 课程的大作业，以 old school 游戏魔兽争霸为背景。

经查证原题来自 [北京大学 程序设计与算法（三）魔兽世界3(2020秋季)](https://cxsjsx.openjudge.cn/2018hwall/024/)。

使用 C++ 编写，`Qt6.5` 增加了图形界面，使用 `cmake` or `xmake` 进行构建。

代码托管在 [Github](https://github.com/Jenway/Warcraft_sdu)上。

在 [Gitee](https://gitee.com/Jenway/Warcraft_sdu) 上 fork了一份。
s

## 编译和运行

支持 C++17 标准的编译器

> ~~因为使用了 智能指针~~ Qt6 需要编译器支持 C++17 标准

CMake
> 切换为更低版本应该也是可以的 (大概)

`Warcraft_CLI` 版本为命令行输入输出，而另一个 `Warcraft` 则是图形界面。

详细的使用方法请参考 [输入样例](./doc/INTRO.md)

## 自动构建

使用 Github Actions 进行自动构建，每次 push tag 时会自动构建，生成的文件会上传到 release 中。

参见 [workflow.yml](./.github/workflows/workflow.yml)
