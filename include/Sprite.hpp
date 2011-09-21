#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "SpriteConfig.hpp" 

class Sprite{
public:

      Sprite(const string&, uint, uint);
      Sprite(const string& name);
      
      Sprite(SpriteData conf):m_frame_count(0), m_current_frame_duration(0){
			m_date=conf;
			}
			
      void SetType(FT::FieldType Ft){ m_type=Ft; }
      FT::FieldType GetType() const { return m_type; }
      
      bool IsMap() const { 
	  if(  m_type == FT::PlatformLeft
	     ||m_type == FT::PlatformDown
	     ||m_type == FT::PlatformRight
	     ||m_type == FT::PlatformUp
	     ||m_type == FT::PlatformHorizontal
	     ||m_type == FT::PlatformVertical	    
	  )
	    return true;
	  return false;
      }
      
      void Update(double);
      void Draw() const;
      void Draw( ushort x, ushort y) const;
      
      void SetPosition(const short X,const short Y){
			 m_date.pos_x=X;  
			 m_date.pos_y=Y; 
		    }
		    
      ushort GetHeight() const { return m_date.height; }
      ushort GetWidth() const { return m_date.width; }
      
      void SetWidth(ushort W){ m_date.width=W; }
      void SetHeight(ushort H){ m_date.height=H; }
      short GetX() const { return m_date.pos_x; }
      void SetX(short x){ m_date.pos_x=x; }
      
      short GetY() const { return m_date.pos_y; }
      void SetY(short y){ m_date.pos_y=y; } 
      
      ushort GetTexX() const { return m_date.tex_x; }
      ushort GetTexY() const { return m_date.tex_y; }  
            
      uint GetFrame() const { return m_frame_count; }	

private:
    FT::FieldType m_type;
    SpriteData m_date;
    uint m_frame_count;
    float m_current_frame_duration;
    
};
typedef boost::shared_ptr<Sprite> SpritePtr;

#endif

