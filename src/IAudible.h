#ifndef _IAUDIBLE_H
#define _IAUDIBLE_H

#include "Audio.h"
#include "IMovable.h"

class IAudible:
    virtual public IMovable
{
    public:

        IAudible() {}
        virtual ~IAudible() {}

    private:
        
        std::map<std::string, std::shared_ptr<Audio::Sound>> m_Sounds;
};

#endif

