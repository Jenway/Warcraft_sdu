// Warrior 战士类

class Warrior
{
private:
    int m_number; // 战士编号
protected:
    int m_life; // 战士生命值
public:
    inline int number() { return this->m_number; } // 获取战士编号
    inline int life() { return this->m_life; }     // 获取战士生命值
    Warrior();
    ~Warrior();
};

// 派生 出 dragon 、ninja、iceman、lion、wolf、五种战士类

// 由于要在主函数中修改战士的生命值，所以将战士的生命值定义为 static 类型

class Dragon : public Warrior
{
private:
    static int default_life; // Drageon 的默认生命值

public:
    inline static void setLife(int life) { default_life = life; }
    Dragon() { this->m_life = default_life; }
    ~Dragon() {}
};

class Ninja : public Warrior
{
private:
    static int default_life; // Ninja 的默认生命值

public:
    inline static void setLife(int life) { default_life = life; }
    Ninja() { this->m_life = default_life; }
    ~Ninja() {}
};

class Iceman : public Warrior
{
private:
    static int default_life; // Iceman 的默认生命值

public:
    inline static void setLife(int life) { default_life = life; }
    Iceman() { this->m_life = default_life; }
    ~Iceman();
};

class Lion : public Warrior
{
private:
    static int default_life; // Lion 的默认生命值

public:
    inline static void setLife(int life) { default_life = life; }
    Lion() { this->m_life = default_life; }
    ~Lion() {}
};

class Wolf : public Warrior
{
private:
    static int default_life; // Wolf 的默认生命值

public:
    inline static void setLife(int life) { default_life = life; }
    Wolf() { this->m_life = default_life; }
    ~Wolf() {}
};