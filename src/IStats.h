#ifndef _ISTATS_H
#define _ISTATS_H

#include <string>
#include <map>
#include <memory>
#include <boost/optional.hpp>
//#include "Stat.h"

class IStats
{
    private:

        //std::vector<Stat> m_Stats;
        std::weak_ptr<Client> m_wpClient;

    public:

        IStats(std::shared_ptr<Client>& client) {
            m_wpClient = client;
        }
        virtual ~IStats() {}
};

#endif

