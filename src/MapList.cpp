#include "MapList.h"
#include "IFallible.h"
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
using namespace std;

MapList :: MapList(const string& fn)
{
    // TODO: remove extra blank lines
    ifstream file(fn);
    if(!file.good()) {
        assert(false);
        throw Failure();
    }
    string buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    boost::split(m_Maps, buffer, boost::is_any_of("\r\n"));
    m_MapItr = m_Maps.begin();
    int i =0;
    foreach(auto& itr, m_Maps) {
        std::cout << i << itr << std::endl;
        i++;
    }
}

