#ifndef CLASS_HPP
#define CLASS_HPP
#include "Heders.hpp"
#include "Game.hpp"

class App {
public:
    explicit App();
    ~App();
    void Run() ;	

private:
    void InitSDL() throw (const char*);

private:
    bool* m_is_done;
    SDL_Surface* m_screen;
    size_t m_screen_h, m_screen_w;    
    Uint32 m_full;
    Gameptr m_game;     
};

#endif
