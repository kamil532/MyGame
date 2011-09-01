#ifndef CLASS_HPP
#define CLASS_HPP
#include "Heders.hpp"
#include "Engine.hpp"
#include "Level.hpp"
#include "SpriteGrid.hpp"
#include "Player.hpp"

class App {

public:
    explicit App();
    void Run() ;

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
    
};

#endif