#ifndef _ISUSPENDABLE_H
#define _ISUSPENDABLE_H

class ISuspendable
{
    private:
        bool m_bSuspended;
    public:
        ISuspendable():
            m_bSuspended(false)
        {}
        bool suspended() const { return m_bSuspended; }
        void suspend(bool t) { m_bSuspended = true; }
};

#endif

