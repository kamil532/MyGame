#ifndef CLASS_HPP
#define CLASS_HPP
#include "Heders.hpp"
#include "Engine.hpp"
#include "Level.hpp"
#include "SpriteGrid.hpp"
#include "Player.hpp"
#include "Menu.hpp"

class App {
public:
    explicit App(const string*);
    ~App();
    void Run() ;	
    void SetAppMode(const string*);

private:
    void InitSDL() throw (const char*);

private:
    bool* m_is_done;
    SDL_Surface* m_screen;
    size_t m_screen_h, m_screen_w;    
    Uint32 m_full;
    Menuptr m_menu;     
};

#endif
