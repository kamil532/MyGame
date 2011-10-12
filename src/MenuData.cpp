#include "MenuData.hpp"

MenuData::MenuData():m_background(NULL), m_title_surf(NULL),
m_current(m_item.begin()),m_menu_str_surf(NULL)
{
      m_sprite_item.reset(new Sprite("menuItem"));
      
      m_color_active.r=160;
      m_color_active.g=208;
      m_color_active.b=8;    
      
   //Napis menu 
   m_menu_str_surf=IMG_Load("data/pic/menu_napis.png");
   if(m_menu_str_surf==NULL )  std::cerr<<"[Error] Not found menu string img\n"; 
   m_menu_str_rect.x=110;
   m_menu_str_rect.y=190;
   
}  

void MenuData::NextItem(){   
      if(m_current!=(--m_item.end())){
      ++m_current;
     m_sprite_item->SetY( m_sprite_item->GetY() + 60);}    
}

void MenuData::PrevItem(){
      l_item_it tmp(m_current);  
      --tmp;
    if( ((tmp)->m_text)=="Resume"
      && !Engine::Get().GetLeveling()->StartedPlay() ) return;
       if(m_current !=(m_item.begin())){
      --m_current;
     m_sprite_item->SetY( m_sprite_item->GetY() - 60);}
}
   
void MenuData::Draw() {    
     l_item_it it(m_item.begin());
     m_sprite_item->Draw();
     //Wyswietlanie wszystkich elementow menu 
     for(; it!=m_item.end(); ++it){
       if( Engine::Get().GetLeveling()->StartedPlay() );
      if(it->m_text=="Resume" && Engine::Get().GetLeveling()->StartedPlay()!=true){
	SDL_Color m_color={100,100,100};
        it->Draw(m_color);
	continue;
      }
	 
	  if(it!=m_current) it->Draw();
	  else it->Draw(m_color_active);
      }     
      
  Engine::Get().GetRenderer()->Draw(m_menu_str_surf,m_menu_str_rect);    
      
}
       
void MenuData::AddItem( MenuItem& Item ){
      m_current=m_item.begin(); 
      m_item.push_back(Item);				   	
}   

void MenuData::SetResume(){ 
      if(m_current->m_text=="New Game"){
	--m_current;     
	 m_sprite_item->SetY( m_sprite_item->GetY() - 60);
      }
}
