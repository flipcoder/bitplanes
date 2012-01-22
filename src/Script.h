#ifndef _SCRIPT_H
#define _SCRIPT_H

#include <string>
#include "IConfig.h"

class Script : public IFallible, public IConfig, public IRealtime
{
    public:
        Script(const std::string& fn):
            IConfig(fn)
        {
            // TODO: cache resources in System::get().imageResources() and System::get().audioResources()
        }
        virtual ~Script() {}

        virtual bool logic(float t) {
            return true;
        }
};

#endif

