#include "Writer.hpp"
#include "Engine.hpp"

Writer::Writer(void):m_font_a(NULL){
  
 m_font_a = TTF_OpenFont( FONT_PATH.c_str(), FONT_SIZE);
 if( !m_font_a)	throw "[Critical] Nie znaleziono fontu"; 
  
 m_font_color.b = 250;
 m_font_color.r = 250;
 m_font_color.g = 250;
			
}

void Writer::WriteString( const string& Text,
		  const SDL_Rect& WhereRect, const SDL_Color& Color){
		    
   SDL_Surface* tmp_surf = TTF_RenderText_Blended( m_font_a,
						   Text.c_str(),
						   Color);
   
   Engine::Get().GetRenderer()->Draw(tmp_surf, WhereRect);   
}

void Writer::WriteString( const string& Text, const SDL_Rect& WhereRect){
		    
   SDL_Surface* tmp_surf = TTF_RenderText_Blended( m_font_a,
						   Text.c_str(),
						   m_font_color);
   
   Engine::Get().GetRenderer()->Draw(tmp_surf, WhereRect);   
}

void Writer::DrawScore(const ulong& Number, const SDL_Rect& Where){
  string Text("Score ");
  std::ostringstream ss;
  ss << Number;
  Text+=ss.str();
  
  WriteString(Text, Where); 
}

