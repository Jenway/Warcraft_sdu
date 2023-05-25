// 这个文件定义了一些枚举类型

#if !defined(ENUMS_HH)
#define ENUMS_HH
#include <vector>

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

const static std::array<std::string, 6> warrior_type_name = {
    "dragon",
    "ninja",
    "iceman",
    "lion",
    "wolf",
    "Count",
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
class inputData {
public:
    int game_round = 0;
    int M = 0, N = 0, K = 0, T = 0;
    std::array<int, 5> default_lives {};
    std::array<int, 5> default_attacks {};
};

class updateData {
public:
    int cityNumber = 0;
    std::vector<WarriorType> redWarrior {};
    std::vector<WarriorType> blueWarrior {};
};
#endif // ENUMS_HH
