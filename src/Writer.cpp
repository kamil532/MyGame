#include "Writer.hpp"
#include "Engine.hpp"

Writer::Writer(void):m_font_a(NULL),
m_screen_height(Engine::Get().GetScreenHeight()),
m_screen_width(Engine::Get().GetScreenWidth()), m_score(0){
  
 m_font_a = TTF_OpenFont( FONT_PATH.c_str(), 42);
 if( !m_font_a)	throw "[Critical] Nie znaleziono fontu"; 
 
 m_score_rect.x =0.8 * m_screen_width;
 m_score_rect.y = 10;
 m_score_rect.h = 200;
 m_score_rect.w = 200;
 
 m_font_color.b = 250;
 m_font_color.r = 250;
 m_font_color.g = 250;
		
	
 m_score_string="Score: 0";
}

void Writer::Render(void){


  m_score_surface=TTF_RenderText_Blended( m_font_a, 
					  m_score_string.c_str(),
					  m_font_color );
  
  Engine::Get().GetRenderer()->Draw( m_score_surface, m_score_rect );

}
void Writer::SetScore(ulong Number){
  m_score_string.clear();
  m_score_string="Score: ";

std::ostringstream ss;
ss << Number;
m_score_string+= ss.str();

m_score = Number;  
}