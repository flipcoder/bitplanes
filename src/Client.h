#ifndef _CLIENT_H
#define _CLIENT_H

#include "IControllable.h"

class Client
{
    public:

        Client(const std::string& name):
            m_sName(name)
        {}
        virtual ~Client() {}

        Color color() const { return m_Color; }
        void color(const Color& c) {
            m_Color = c;
        }

        std::string name() { return m_sName; }
        const std::string name() const { return m_sName; }
        void name(std::string n) {
            m_sName = n;
        }

    private:
        
        std::vector<std::weak_ptr<IControllable>> m_Nodes;
        std::string m_sName;
        
        Color m_Color;
};

#endif

