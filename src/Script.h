#ifndef _SCRIPT_H
#define _SCRIPT_H

#include <string>
#include <fstream>
#include "IFallible.h"
#include "IConfigurable.h"
#include "IRealtime.h"

class Script : public IFallible, public IConfigurable, public IRealtime
{
    private:
        std::ifstream m_Script;

    public:
        Script(const std::string& fn);
        virtual ~Script() {}

        virtual bool logic(float t) {
            return true;
        }

        // Load in resources used by script
        void precache();
};

#endif

