#ifndef _SCRIPT_H
#define _SCRIPT_H

#include <string>
#include <fstream>
#include "IFallible.h"
#include "IConfig.h"
#include "IRealtime.h"

class Script : public IFallible, public IConfig, public IRealtime
{
    private:
        std::ifstream m_Script;

    public:
        Script(const std::string& fn);
        virtual ~Script() {}

        virtual bool logic(float t) {
            return true;
        }

        void precache();
};

#endif

