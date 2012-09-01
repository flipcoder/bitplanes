#ifndef _MAPLIST_H
#define _MAPLIST_H

#include <string>
#include <vector>

class MapList
{
    public:

        MapList(const std::string& fn);
        ~MapList() {}

        std::string current() { return *m_MapItr; }

        bool done() const { return m_MapItr==m_Maps.end(); }
        bool next() {
            if(m_MapItr==m_Maps.end())
                return false;
            ++m_MapItr;
            return m_MapItr!=m_Maps.end();
        }
        
        // TODO: return progress
        //float progress() {
        //    return 0.0f;
        //}

    private:
        
        std::vector<std::string> m_Maps;
        std::vector<std::string>::iterator m_MapItr;
};

#endif

