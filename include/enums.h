// 这个文件定义了一些枚举类型

#if !defined(ENUMS_HH)
#define ENUMS_HH

#include <array>
#include <string>

enum class head_color {
    red,
    blue,
    Count
};

const static std::array<std::string, 2> head_color_name = {
    "red",
    "blue",
};

enum class WarriorType {
    dragon,
    ninja,
    iceman,
    lion,
    wolf,
    Count
};

const static std::array<std::string, 5> warrior_type_name = {
    "dragon",
    "ninja",
    "iceman",
    "lion",
    "wolf",
};

enum class WeaponType {
    sword,
    bomb,
    arrow,
    Count
};

const static std::array<std::string, 3> weapon_type_name = {
    "sword",
    "bomb",
    "arrow",
};

#endif // ENUMS_HH
