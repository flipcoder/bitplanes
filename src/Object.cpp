#include "Object.h"

Object :: Object(const std::string& fn)
{
    nullify();
    if(!m_Properties.open(fn.c_str()))
    {
        setError("Failed to load object \"" + fn + "\"");
        throw Failure();
    }
}

Object :: ~Object()
{
    
}

