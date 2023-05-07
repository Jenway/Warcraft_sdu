# 期末大作业 `魔兽争霸`

## 说明

这是 SDU 计科专业 2022 级 `高级程序语言设计` 课程的大作业，以 old school 游戏魔兽争霸为背景。

使用 C++ 编写，使用 CMake 进行构建。

代码托管在 [Github](https://github.com/Jenway/Warcraft_sdu)上。

预计在 [Gitee](https://gitee.com/Jenway/Warcraft_sdu) 上 fork 一份。

## 使用

暂定只通过控制台进行输入输出，不使用图形界面。

详细的使用方法请参考 [输入样例](./doc/INTRO.md)

## 编译

需要编译器支持 C++14 标准 (因为使用了 智能指针)

虽然 CMakeLists.txt 要求的最低版本为 3.16，但是切换为更低版本应该也是可以的 (大概)

## 实验报告的 Draft

### 最终完成的任务难度

最终完成的任务难度为 `难度三` ,完成了基本要求和部分附加要求

### 程序文件的组织架构

### include\Warrior.h && src\Warrior.cpp

抽象 `Warrior` ,战士类

包含属性如下:

- m_life 生命值
- m_number 战士
- m_attack 攻击力
- m_weapon 武器

派生出 `dragon` 、`ninja`、`iceman`、`lion`、`wolf`、五种战士类

包含属性:

| 战士派生类 | 武器 | 属性 | 技能
| :--------: | :--: | :--: | :--: |
|   dragon   |  n%3 | 士气 | 战斗结束后,如果还没有战死,就会欢呼 |
|   ninja    | n%3, (n+1)%3 | 无 | 使用 bomb 不受伤 |
|   iceman   | n%3 | 移动后生命值减少 | 移动后攻击力增加 |
|    lion    | 无 | 士气 | 每战斗一次,士气降低 K |
|    wolf    | 无 | 无 | 抢夺敌人武器 |

- default_life 每个战士都设置的单独的静态变量，储存其默认生命值

### include\Weapon.h

| 武器 | 攻击力 | 耐久度 |
| :--: | :----: | :----: |
| sword | 0.2 *| 无限 |
| bomb | 0 | 1 |
| arrow | 0.3 *| 2|

### include\Headquarter.h && src\Headquater.cpp

抽象 `Headquarter` 司令部类

### include\City.h

抽象 `City` 城市类

### include\Enum.h

### 程序完成的主要逻辑

## 收获与感想

配置 cmake比上次写 (已经鸽掉的) 小恐龙有了些许进步。嘛，可能是因为还没用第三方库的原因。

设计模式，`chatgpt` 告诉我工厂模式这种设计模式，让我不禁感慨自己知识的匮乏，看来，不只需要学习语言特性与轮子，还需要学习设计模式等等。

> warning C4819: 该文件包含不能在当前代码页(936)中表示的字符。请将该文件保存为 Unicode 格式以防止数据丢失

`add_compile_options("$<$[C_COMPILER_ID:MSVC](C_COMPILER_ID:MSVC):/source-charset:utf-8>")`

遇到了循环依赖的问题，解决方法是使用前向声明，但是这样就不能使用 `unique_ptr` 了，因为 `unique_ptr` 需要知道完整的类型信息。

还尝试使用了抽象接口类，这样使得程序更加灵活，但是也带来了一些问题，容易又回到循环依赖的问题。

于是，我就把 `unique_ptr` 换成了 `shared_ptr`。为了实现,多个对象之间共享所有权侧重于生命周期控制,还使用了 `weak_ptr`
