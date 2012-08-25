#ifndef _IOWNABLE_H
#define _IOWNABLE_H

#include <memory>

class IOwnable
{
    public:
        
        //std::weak_ptr<> m_wpOwner; // <- way to associate specific groups (adapter for singleplayers and teams both)

        enum eOwner {
            O_NONE = 0,
            O_FRIENDLY,
            O_ENEMY
        };

        IOwnable() {
            m_Owner = O_NONE;
        }
        virtual ~IOwnable() {}

        void owner(eOwner owner) {
            m_Owner = owner;
        }
        eOwner owner() const {
            return m_Owner;
        }

    private:
        
        eOwner m_Owner;
};

#endif

