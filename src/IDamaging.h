#ifndef _IDAMAGING_H
#define _IDAMAGING_H

class IDamaging
{
public:
    IDamaging(int damage = 0) {
        m_Damage = damage;
    }

    virtual ~IDamaging() {}

    int damage() const { return m_Damage; }
    void damage(int d) { m_Damage = d; }

private:
    int m_Damage;
};

#endif

