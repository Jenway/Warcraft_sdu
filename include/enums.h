// 这个文件定义了一些枚举类型

#if !defined(ENUMS_HH)
#define ENUMS_HH

#include <array>
#include <string>

enum class head_color
{
    red,
    blue
};

enum class WarriorType
{
    dragon,
    ninja,
    iceman,
    lion,
    wolf,
    Count
};

const static std::array<std::string, 5> warrior_type_name =
    {
        "dragon",
        "ninja",
        "iceman",
        "lion",
        "wolf",
};

#endif // ENUMS_HH
