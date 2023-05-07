#if !defined(ABSTRACT_CITY_H)

#define ABSTRACT_CITY_H

#include "Enums.h"
#include <memory>

class Warrior;
class AbstractCity {
public:
    // 获取需要的信息
    virtual AbstractCity& nextCity() = 0;
    virtual AbstractCity& previousCity() = 0;
    virtual bool isHeadquarter() const = 0;
    virtual void addWarrior(std::shared_ptr<Warrior> warrior, head_color color) = 0;
    virtual ~AbstractCity() = default;
};
#endif // ABSTRACT_CITY_H