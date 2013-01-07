#ifndef _IDESTROYABLE_H
#define _IDESTROYABLE_H

class IDestroyable {
private:

    int m_Health;
    int m_MaxHealth;

public:

    IDestroyable(int health = 1) {
        m_Health = m_MaxHealth = health;
    }
    virtual ~IDestroyable() {}
    
    int hurt(int hp) {
        int damage = std::min(hp, m_Health);
        m_Health -= damage;
        return damage;
    }
    bool hurt() const { return m_Health < m_MaxHealth; }
    bool dead() const { return m_Health <= 0; }
    int health(int health) {
        int old = m_Health;
        m_Health = std::min(std::max(health, 0), m_MaxHealth);
        return m_Health - old;
    }
    int maxHealth(int max) {
        int old = m_MaxHealth;
        m_MaxHealth = std::max(0, max);
        return m_MaxHealth - old;
    }

    int health() const { return m_Health; }
    int maxHealth() const { return m_MaxHealth; }
};

#endif

