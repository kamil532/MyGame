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
    void Draw() const;
    void ProcessEvents();
    void Update(double);
    void InitSDL() throw (const char*);

private:
    SDL_Surface* m_screen;
    bool m_is_done;
    size_t m_screen_h, m_screen_w;
    
    LevelPtr m_level;
    SpriteGrid m_grid;
    PlayerPtr m_player;
    Uint32 m_full;
    Menuptr m_menu;
    SDL_Event event;
    
};

#endif
