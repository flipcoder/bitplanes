#include "GameState.h"
#include "Client.h"
 
GameState :: GameState()
{
    // load the current map
    //std::cout<< (str("data/maps/") + System::get().session()->maps()->current() + ".lua") <<  std::endl;
    m_spWorld.reset(new World(str("data/maps/") + System::get().session()->maps()->current() + ".lua"));

    // initialize a plane for each client/player (only 1 right now)
    std::vector<std::shared_ptr<Client>> clients = System::get().session()->clients();
    foreach(auto& cl, clients)
    {
        std::shared_ptr<Player> player(new Player("plane1.ini", cl));
        m_Players.push_back(player);
        m_spWorld->add(player);
    }

    //m_spWorld->time()->speed(0.1f);
}

GameState :: ~GameState()
{
    
}

bool GameState :: playersDead() const
{
    foreach(auto& player, m_Players)
    {
        if(! player->invalid())
            return false;
    }
    return true;
}

void GameState :: logic(float t)
{
    if(Events::get().key(ALLEGRO_KEY_F10)) {
        System::get().quit();
        return;
    }if(Events::get().key(ALLEGRO_KEY_ESCAPE)){
        //System::get().pushState("pause")
        System::get().quit(); // temp
        return;
    }

    t = m_GameTime.logic(t);
    m_spWorld->logic(t);

    // replace with some sort of mode state logic
    if(m_spWorld->done())
    {
        if(System::get().session()->maps()->next()) // attempt to go to next map?
            System::get().swapState("game"); // continue playing
        else
            System::get().swapState("title"); // the end, go to menu

        return;
    }

    if(m_aAfterDeath)
    {
        if(m_aAfterDeath->hasElapsed()) {
            System::get().swapState("game"); // restart
        }
    }
    else if(playersDead())
        m_aAfterDeath = Freq::Alarm(Freq::Time(1000), m_spWorld->time());
}

