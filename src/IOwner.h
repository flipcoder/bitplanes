#ifndef _IOWNER_H
#define _IOWNER_H

class IOwner
{
    public:
        
        enum eOwner {
            O_NONE = 0,
            O_FRIENDLY,
            O_ENEMY
        };

        IOwner() {
            m_Owner = O_NONE;
        }
        virtual ~IOwner() {}

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

