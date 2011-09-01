#include "Renderer.hpp"


Renderer::Renderer(SDL_Surface* Screen, const string& filename)
		:m_screen(Screen), m_atlas(NULL) {				
			m_atlas =
			//SDL_DisplayFormat(
			IMG_Load(filename.c_str())
			//	 )
			; 

			if (!m_atlas) {	throw "[Critical] Not found sprite atlas file\n"; }			
}

void Renderer::Draw(size_t tex_x, size_t tex_y,
				  size_t pos_x, size_t pos_y,
				  size_t width, size_t height ){
					  
   if (m_screen==NULL) throw "[Critical] Renderer don`t have draw surface";
   
   /// Info o surface w atlasie
   SDL_Rect b={tex_x,tex_y,width,height};  
   
   /// Info o surface na ekranie
   SDL_Rect a={pos_x,pos_y,width,height};
   
   /// Odbijanie dpowiedniego fragmentu atlasu na ekranie
   SDL_BlitSurface(m_atlas, &b , m_screen, &a);				  
					  
}

void Renderer::Draw(const Sprite* _Sprite, uint frame=0 ){
	
  if (m_screen==NULL) throw "[Critical] Renderer don`t have draw surface";
	 
   /// Info o surface w atlasie 
   SDL_Rect b={ _Sprite->GetTexX() + (frame * _Sprite->GetWidth()),
				_Sprite->GetTexY(),
				_Sprite->GetWidth(),
				_Sprite->GetHeight() };  
   
   /// Info o surface na ekranie
   SDL_Rect a={ _Sprite->GetX(),
				_Sprite->GetY(),
				_Sprite->GetWidth(),
				_Sprite->GetHeight() };
   
   /// Odbijanie dpowiedniego fragmentu atlasu na ekranie
   SDL_BlitSurface(m_atlas, &b , m_screen, &a);				  
					  
}
	
void Renderer::Draw(const SpritePtr _Sprite ){
	
	 if (m_screen==NULL) throw "[Critical] Renderer don`t have draw surface";
	 
   /// Info o surface w atlasie 
   SDL_Rect b={ _Sprite->GetTexX() + (_Sprite->GetFrame() * _Sprite->GetWidth() ),
				_Sprite->GetTexY(),
				_Sprite->GetWidth(),
				_Sprite->GetWidth() };  
   
   /// Info o surface na ekranie
   SDL_Rect a={ _Sprite->GetX(),
				_Sprite->GetY(),
				_Sprite->GetWidth(),
				_Sprite->GetWidth() };
   
   /// Odbijanie dpowiedniego fragmentu atlasu na ekranie
   SDL_BlitSurface(m_atlas, &b , m_screen, &a);	
}		

void Renderer::Draw( SDL_Surface* _Surface,SDL_Rect dest){

    SDL_BlitSurface(_Surface, NULL , m_screen, &dest);	 
}

void Renderer::Draw(SDL_Surface* _Surface){
      
      SDL_BlitSurface(_Surface,NULL , m_screen, NULL);	 
}