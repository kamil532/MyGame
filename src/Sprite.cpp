#include "Sprite.hpp"
#include "Engine.hpp"


Sprite::Sprite(const string& name,uint X,uint Y): m_frame_count(0), m_current_frame_duration(0){ 
	   
     m_date = Engine::Get().GetSpriteConfig()->Get(name);  
     m_date.pos_x=X; 
     m_date.pos_y=Y;  
     
} 

Sprite::Sprite(const string& name):m_frame_count(0), m_current_frame_duration(0){    
				 m_date = Engine::Get().GetSpriteConfig()->Get(name);  
} 

void Sprite::Draw() const{
	Engine::Get().GetRenderer()->Draw(this , m_frame_count); 
}  

void Sprite::Draw(ushort x, ushort y) const{
	
	Engine::Get().GetRenderer()->Draw(
				 m_date.tex_x,
				 m_date.tex_y,
				 x,
				 y,
				 m_date.width,
				 m_date.height	); 
} 

void Sprite::Update(double time){
  
 m_current_frame_duration+=time;

    if(m_current_frame_duration >= m_date.frame_time){
	  ++m_frame_count;
	  m_current_frame_duration-=m_date.frame_time;      
    }
    
    if(m_frame_count>= m_date.frame_count){
	if(m_date.loop){
	  m_frame_count=0;
	}
	else{
	 --m_frame_count; 
	}   
    }

}  


