#ifndef _LOBBYSTATE_H
#define _LOBBYSTATE_H

#include "IState.h"

class LobbyState:
    public IState
{
    public:

        LobbyState() {}
        ~LobbyState() {}
        void logic(float t) {}
        void render() const {}

    private:
        
        
};

#endif

