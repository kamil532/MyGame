#ifndef LEVELING_HPP
#define LEVELING_HPP
#include "Heders.hpp"
#include "Sprite.hpp"

// klasa ma zarzadzac levelami
// zapisywac, ktore juz przeszadl gracz, trzymac ilosc punktow w aktualnej grze...
// klasa pokazuje po kazdym levelu info o zdobytych punkta
 
class Leveling{
public:
    Leveling();
    void NextLevel();
    void AddScore(const ulong& Score){
      m_score+=Score;
    }

    bool PlayerDie();
   
    
    bool StartedPlay() const { return m_started_game; }
    void StartNewGame(){ m_started_game=true; } 
    void StartGame();  
    
    void SetPlayerDie(){ m_player_life=false; }
    void SetGameStatePtr(GS::GameState* S){ m_game_state=S; }
    
    ulong  GetScore() const { return m_score; }
    ushort GetLevelNumber() const { return m_current; }
    
private: 
   GS::GameState* m_game_state; 
   SDL_Event m_event;  
   ulong m_score;
   ulong m_highscore;
   ushort m_current; 

   bool m_started_game;
   bool m_player_life;
   
   SDL_Surface* m_background;
   SDL_Surface* m_level_surf;

   SDL_Rect m_back_rect;   
   SDL_Rect m_level_number_rect;
   
};
typedef boost::shared_ptr<Leveling> LevelingPtr;

#endif
