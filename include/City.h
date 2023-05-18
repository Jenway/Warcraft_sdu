#if !defined(CITY_H)
#define CITY_H

#include "../include/AbstractCity.h"

class City : public AbstractCity {

private:
    int cityNumber = 0;

public:
    // override
    std::shared_ptr<AbstractCity> nextCity(head_color color) override { return color == head_color::red ? m_rightCity : m_leftCity; }
    int getCityNumber() override { return cityNumber; }
    City(int number)
        : cityNumber(number)
    {
        this->isThisHeadquater = false;
    }
    virtual ~City() { }
};

#endif
