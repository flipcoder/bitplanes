#ifndef _SESSION_H
#define _SESSION_H

// Keeps game and client information, passed between engine states if necessary
#include <memory>
#include <map>
#include <tuple>
#include "Client.h"
#include "MapList.h"

class Session
{
    public:

        Session() {
            m_Clients[0].reset(new Client("default"));
            m_MapList.reset(new MapList("data/maps/map.list"));
        }
        virtual ~Session() {}

        MapList* maps() { return m_MapList.get(); }
        const MapList* maps() const { return m_MapList.get(); }

        std::vector<std::shared_ptr<Client>> clients() {
            std::vector<std::shared_ptr<Client>> vec;
            vec.reserve(m_Clients.size());
            foreach(auto client, m_Clients)
                vec.push_back(client.second);
            return vec;
        }
        
    private:
        
        std::map<unsigned int, std::shared_ptr<Client>> m_Clients;
        std::shared_ptr<MapList> m_MapList;
};

#endif

