#include "Menu.hpp"

Menu::Menu():m_show(true), m_game_state(GS::MainMenu),m_menuTlo(NULL),
m_about(NULL)
{
  SDL_Rect tmpRect={ 400, 280, 100,40 };
  m_menu_main.reset(new MenuData());  
 
  //Napisy w menu glownym
  m_menu_main->AddItem(*(new MenuItem(*(new string("Resume")),tmpRect)));
  tmpRect.y+=60; 
 
  m_menu_main->AddItem(*(new MenuItem(*(new string("New Game")),tmpRect)));
  tmpRect.y+=60; 
 
  m_menu_main->AddItem(*(new MenuItem(*(new string("About")),tmpRect)));
  tmpRect.y+=60; 
 
  m_menu_main->AddItem(*(new MenuItem(*(new string("Exit")),tmpRect)));
  
  m_date_rect.x = ( Engine::Get().GetScreenWidth()-180 )/2;
  m_date_rect.y = Engine::Get().GetScreenHeight()*0.9; 

  //Tlo w menu
  m_menuTlo=IMG_Load("data/pic/menu.png");
  
 if (m_menuTlo == NULL ) throw "[Critical] Background for menu not found\n";
 
  //prawy dolny rog
  m_menuTlo_rect.x=0;
  m_menuTlo_rect.y=0;
 
  //Obrazek about
  m_about=IMG_Load("data/pic/about.png");
  if( m_about == NULL ) std::cerr<<"[Error] Not found about info\n";
  m_about_rect.x=130;
  m_about_rect.y=230;
 
}

void Menu::PressReturn(){
  
 if(m_game_state==GS::MainMenu){
    if( (m_menu_main -> GetValueCurrent())=="New Game"){      
      //m_game_state=GS::NewGame;
      m_game_state=GS::SelectLevel;        
    }
    if( (m_menu_main -> GetValueCurrent())=="Exit")  
	*m_is_done=true;    
    }
    if( (m_menu_main -> GetValueCurrent())=="Resume"){
	m_game_state=GS::Play;
    }
     if( (m_menu_main -> GetValueCurrent())=="About"){
	m_game_state=GS::About;
   }  
}

void Menu::Draw(){
  
  //Tlo dla menu  
  Engine::Get().GetRenderer()->Draw(m_menuTlo,m_menuTlo_rect);
  
  if ( m_game_state == GS::MainMenu ){
       m_menu_main->Draw();  
    } 
    
  if ( m_game_state == GS::About ){
    Engine::Get().GetRenderer()->Draw(m_about, m_about_rect);
    }  
   
  if ( m_game_state == GS::SelectLevel ){
    
    
  }
    
    
}

void Menu::Next(){
  if( m_game_state == GS::MainMenu )
    m_menu_main->NextItem();  
}

void Menu::Prev(){
  if( m_game_state == GS::MainMenu )
    m_menu_main->PrevItem();
}



