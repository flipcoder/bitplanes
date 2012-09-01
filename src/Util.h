#ifndef _UTIL_H
#define _UTIL_H

#include <cstdlib>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
//#include <boost/optional/optional.hpp>
//#include <boost/serialization/shared_ptr.hpp>

//typedef signed char byte;
typedef unsigned char ubyte;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;

#define BIT(x) (1<<(x))
//#define MASK(x) (x?((1<<x)|((1<<x)-1)):1)
#define MASK(x) ((1<<(x))-1)
//#define MASK(x) (x?((1<<(x-1))-1):0)

// set bit by bit value (1,2,4,8...)
#define BIT_SET(s,f) s|=(f)
#define BIT_TOGGLE(s,f) s^=(f)
#define BIT_ISSET(s,f) ((s)&(f))
#define BIT_UNSET(s,f) s&=(~(f))

//inline bool xor(bool a, bool b){
//    return a != b;
//}

// set bit by bit index (1,2,3,4,5...)
#define FLAG_SET(s,f) s|=((1<<(f)))
#define FLAG_TOGGLE(s,f) s^=((1<<(f)))
#define FLAG_ISSET(s,f) ((s)&(1<<(f)))
#define FLAG_UNSET(s,f) s&=(~(1<<(f)))

//#define MIN(a,b) ((a)<(b)?(a):(b))
//#define MAX(a,b) ((a)>(b)?(a):(b))

#define until(x) while(!(x))

#define foreach BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

// old way, not compatible:
//#define foreach(itr, x) for(auto itr = (x).begin(); itr != (x).end(); ++itr)

//if(false){}else{assert(x);}
//#define ASSERT assert
//#ifdef _DEBUG
//   #define ASSERT(x) assert(x)
//#else
//   #define ASSERT(x) ((void*)0)
//#endif

//#define DEG2RAD(X) ((X)*M_PI/180.0)
//#define RAD2DEG(X) ((X)*180.0/M_PI)
//#define DEG2RADf(X) ((X)*(float)M_PI/180.0f)
//#define RAD2DEGf(X) ((X)*180.0f/(float)M_PI)

//inline double round(double r) {
//    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
//}
//inline float round(float r) {
//    return (r > 0.0f) ? floor(r + 0.5f) : ceil(r - 0.5f);
//}
inline int round_int(double r) {
    return (int)( (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5) );
}
inline int round_int(float r){
    return (int)( (r > 0.0f) ? floor(r + 0.5f) : ceil(r - 0.5f) );
}
inline unsigned int round_uint(double r){
    return (int)( (r > 0.0f) ? floor(r + 0.5f) : ceil(r - 0.5f) );
}
inline unsigned int round_uint(float r){
    return (int)( (r > 0.0f) ? floor(r + 0.5f) : ceil(r - 0.5f) );
}
//double round(double r, int precision)
//{
//    std::stringstream ss;
//    ss << std::setprecision(precision) << std::setiosflags(std::ios_base::fixed) << val;
//    ss >> r;
//    return r;
//}
//float round(float r, int precision)
//{
//    std::stringstream ss;
//    ss << std::setprecision(precision) << std::setiosflags(std::ios_base::fixed) << val;
//    ss >> r;
//    return r;
//}

template <class T>
inline std::string str(const T& t)
{
    std::ostringstream ss;
    ss << t;
    return ss.str();
}

// NOTE: just use lexical_cast
//template <class T>
//boost::optional<T> from_str(const std::string& s)
//{
//    std::istringstream iss(s);
//    boost::optional<T> t;
//    if(iss >> *t)
//        return t;
//    return boost::optional<T>();
//}

//template <class T>
//inline T sgn(const T& t)
//{
//    if(t > T(0.0) + T(EPSILON))
//        return T(1.0);
//    if(t < T(0.0) - T(EPSILON))
//        return T(-1.0);
//    return T(0.0);
//}

template <class T>
inline bool stringBeginsWith(T str, const T& begin) {
    if(str.empty() || begin.size() > str.size())
        return false;
    str = str.substr(0,begin.length());
    return(str.compare(begin)==0);
}

template <class T>
inline bool stringEndsWith(T str, const T &end) {
    if(str.empty() || end.size() > str.size())
        return false;
    str = str.substr(str.length() - end.length());
    return(str.compare(end)==0);
}

inline void explode(char delim, const std::string &str, std::vector<std::string>& vec)
{
    std::stringstream ss(str);
    std::string s;
    while(std::getline(ss, s, delim))
    {
        if(s!="")
            vec.push_back(s);
    }
}

inline std::vector<std::string> explode(char delim, const std::string &str)
{
    std::vector<std::string> vec;
    
    std::stringstream ss(str);
    std::string s;
    while(std::getline(ss, s, delim))
    {
        if(!s.empty())
            vec.push_back(s);
    }
    return vec;
}

inline std::string repeat(const std::string word, int times)
{
    std::string result;
    result.reserve(times*word.length());
    for (int a = 0; a < times; a++)
        result += word;
    return result;
}
//#ifdef _DEBUG
//    #define if_ASSERT(x) if(!(x)) {assert(x)} else if(false)
//#else
//    #define if_ASSERT(x) if(!(x))
//#endif
inline std::string trim(const std::string &s, const std::string &chars = std::string(" "))
{
    size_t last = s.find_last_not_of(chars);
    if (last == std::string::npos) return "";
    size_t first = s.find_first_not_of(chars);
    if (first == std::string::npos) first = 0;
    return s.substr(first, (last-first)+1);
}

template<class T, class U>
bool push_back_unique(T& container, const U& element)
{
    //for(container::const_iterator itr = container.begin();
    //    itr != container.end();
    //    ++itr)
    //{
    //    if(element == *itr)
    //        return false;
    //}
    if(std::find(container.begin(), container.end(), element) == container.end())
    {
        container.push_back(element);
        return true;
    }
    return false;
}



//#define NO_DEALLOCATOR boost::serialization::null_deleter()

#define SCOPED_ENUM_TYPE(blah) uint32_t
#define SCOPED_ENUM(blah) struct blah {enum // enum class {
    // enum class {
#define END_SCOPED_ENUM() ;};
    
//
//#define SCOPED_ENUM_TYPE(blah) blah
//#define SCOPED_ENUM(blah) enum class blah {
//#define END_SCOPED_ENUM()
// ;
//

template<class T>
T safe_ptr(T ptr)
{
    if(!ptr)
        throw std::runtime_error("Null Pointer Exception");
    return ptr;
}

template <class T>
class scoped_dtor {
    private:
        T* m_object;
    public:
        scoped_dtor(T* o):
            m_object(o)
        {}

        ~scoped_dtor(){
            call();
        }

        void call() {
            if(m_object)
                m_object->~T();
        }

        void resolve() {
            m_object = NULL;
        }

        void now() {
            call();
            resolve();
        }
};

#endif

