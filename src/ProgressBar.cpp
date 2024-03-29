#include "ProgressBar.hpp"

ProgressBar::ProgressBar(const SDL_Rect& borderRec, const SDL_Rect& fillingRec):
m_empty(false), m_full(true),m_width_bar(borderRec.w),m_width_uses(fillingRec.w),
m_long_bar(fillingRec.w)
{
  m_border.reset(new Sprite("livebar", borderRec.x, borderRec.y));
  m_filling.reset(new Sprite("livebarback", fillingRec.x, fillingRec.y )); 
  
  m_border->SetHeight(borderRec.h);
  m_border->SetWidth(borderRec.w);
  
  m_filling->SetHeight(fillingRec.h);
  m_filling->SetWidth(fillingRec.w);
}

void ProgressBar::Update( const double& Current_state){
  
  if( Current_state > 1.05 || Current_state < 0 ) {
    std::cerr<<"[Error] Zla wartosc dlugosci paska";
    return;    
  }
  m_width_uses = m_long_bar * Current_state;
  if( m_width_uses == m_long_bar ){ m_full=true; m_empty=false; }
  if( m_width_uses == 0 ){ m_empty=true; m_full=false;}
  
  m_filling->SetWidth( m_width_uses );
  
}

bool ProgressBar::LessThen(const double& Value) const{
    if(m_width_uses > Value) return true;
    else return false;  
}


void ProgressBar::Draw() const {
   m_filling->Draw(); //wypelnienie paska 
   m_border->Draw();  //ramka paska
}