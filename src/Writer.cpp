#include "Writer.hpp"
#include "Engine.hpp"

Writer::Writer(void):m_font_a(NULL){
  
 m_font_a = TTF_OpenFont( Engine::GetLua()->FONT_PATH.c_str(), Engine::GetLua()->FONT_SIZE);
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
   
   SDL_FreeSurface( tmp_surf );
}

void Writer::WriteString( const string& Text, const SDL_Rect& WhereRect){
		    
   SDL_Surface* tmp_surf = TTF_RenderText_Blended( m_font_a,
						   Text.c_str(),
						   m_font_color);
   
   Engine::Get().GetRenderer()->Draw(tmp_surf, WhereRect);  
   
   SDL_FreeSurface( tmp_surf );
}

void Writer::DrawScore(const ulong& Number, const SDL_Rect& Where){
  string Text("Score:");
  std::ostringstream ss;
  ss << Number;
  Text+=ss.str();
  
  WriteString(Text, Where, 35); 
}

void Writer::WriteString(const string& Text, 
		   const SDL_Rect& WhereRect,
		   const uint& Size){		    
  TTF_Font* tmp= 
	  TTF_OpenFont( Engine::GetLua()->FONT_PATH.c_str(), Size);
	  
  SDL_Surface* tmp_surf = 
	  TTF_RenderText_Blended( tmp, Text.c_str(),m_font_color );   
	  
  Engine::Get().GetRenderer()->Draw(tmp_surf, WhereRect);    
  
  SDL_FreeSurface( tmp_surf );
  TTF_CloseFont( tmp );
  
}
		   
		   
		   