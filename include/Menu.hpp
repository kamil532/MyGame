#ifndef MENU_HPP
#define MENU_HPP
#include "Heders.hpp"
#include "MenuData.hpp"

class Menu{
public: 
     explicit Menu();
     void Draw();
     bool IsShow(){ return m_show; }
     bool IsMainMenu(){ 
       if(m_game_state==GS::MainMenu) return true; return false;        
      }
          
     GS::GameState GetGameState(void) const { return m_game_state; }
     GS::GameState* GetGameStatePtr() { return &m_game_state; }
     
     void Next();  
     void Prev();
     void PressReturn();   
     void SetQuitFlag( bool* Done ){ m_is_done=Done; }  
     void SetResume()const { m_menu_main->SetResume(); }
     
private: 
     MenuDataPtr m_menu_main;
     bool m_show;
     GS::GameState m_game_state; 
     bool* m_is_done;  
     
     SDL_Surface* m_menuTlo;
     SDL_Surface* m_about;
     
     SDL_Rect m_about_rect;
     SDL_Rect m_date_rect;
     SDL_Rect m_menuTlo_rect;

};

typedef boost::shared_ptr<Menu> MenuPtr;

#endif