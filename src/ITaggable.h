#ifndef _ITAGGABLE_H
#define _ITAGGABLE_H

#include <string>
#include <set>
#include "Util.h"

class ITaggable
{
    private:
        std::set<std::string> m_Tags;
    public:
        ITaggable() {}
        ITaggable(const std::string& fn) {
            m_Tags.insert(boost::algorithm::to_lower_copy(fn));
        }
        virtual ~ITaggable() {}
        
        bool tag(const std::string& fn) {
            return m_Tags.insert(boost::algorithm::to_lower_copy(fn)).second;
        }
        bool untag(const std::string& fn) {
            m_Tags.erase(m_Tags.find(boost::algorithm::to_lower_copy(fn)));
        }
        unsigned int numTags() { return m_Tags.size(); }
        bool hasTags() { return m_Tags.empty(); }

        bool tag(const std::string& fn) const {
            //return false;
            return m_Tags.find(boost::algorithm::to_lower_copy(fn)) != m_Tags.end();
        }
};

#endif

