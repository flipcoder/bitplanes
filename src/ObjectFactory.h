#ifndef _OBJECTFACTORY_H
#define _OBJECTFACTORY_H

#include <memory>
#include "Object.h"

namespace ObjectFactory
{
    std::shared_ptr<Object> create(const std::string& name);
};

#endif

