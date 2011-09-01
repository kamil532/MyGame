#include "SpriteGrid.hpp"
#include "Engine.hpp"

SpriteGrid::SpriteGrid():m_level_height(0),m_level_width(0),
 m_background( IMG_Load("data/tex.bmp"))
{ 	  
  if( m_background == NULL ) throw "[ERROR] No background found";	}

void SpriteGrid::StoreSprite(FT::FieldType ft, SpritePtr Sprite){
  //dodawanie sprite do bazy danych tej klasy
  if ((m_sprites.size() <= static_cast<size_t> (ft)))  
			    m_sprites.resize(ft + 1);
  m_sprites.at(ft) = Sprite;  
}

void SpriteGrid::SetLevel( LevelPtr Level){

    m_level = Level;
    m_level_height= Level -> GetHeight();
    m_level_width= Level -> GetWidth();
    
    
    m_grid.resize(Level->GetHeight());
    for (size_t i = 0; i < m_level_height; ++i) {
        m_grid.at(i).resize( m_level_width ); 
    }

     for ( ushort y = 0; y < m_grid.size(); ++y){
	vector <SpritePtr> & row = m_grid.at(y);
	  for( ushort x = 0; x < row.size(); ++x){
	    const FT::FieldType& ft = m_level ->GetField(x,y);
	    if( ft>0 ){
	      SetSprite( x, y, m_sprites.at(ft),ft); 		
	      }	if (ft>=4){
		SDL_Rect tmp={CORNER_X + TILE_SIZE * x,
			      CORNER_X + TILE_SIZE * y,
			      TILE_SIZE*2,TILE_SIZE*2};
			      
			      Engine::Get().GetTreasure()->AddTreasure(tmp);
	      }
		
		
	      
	  }
     }
   
     for (size_t y = 0; y < m_grid.size(); ++y) {
            const std::vector<SpritePtr>& row = m_grid.at(y);
		for (size_t x = 0; x < row.size(); ++x) {
		  const SpritePtr& sprite = row.at(x);
		  if(sprite){		
			  sprite->SetX(CORNER_X + TILE_SIZE * x);
			  sprite->SetY(CORNER_X + TILE_SIZE * y);
			  SDL_Rect tmp;
			  tmp.x = sprite->GetX();
			  tmp.y = sprite->GetY();
			  tmp.h = TILE_SIZE;
			  tmp.w = TILE_SIZE;
			  
			  if(sprite->GetType() < 4 ) //![ilosc elementow mapy]
			  Engine::Get().GetAabb()->AddBox(tmp);
		  }
		}
     } 
     
}

void SpriteGrid::Draw() const{

Engine::Get().GetRenderer()->Draw(m_background);
  
     for (size_t y = 0; y < m_grid.size(); ++y) {
            const std::vector<SpritePtr>& row = m_grid.at(y);
		for (size_t x = 0; x < row.size(); ++x) {
		  const SpritePtr& sprite = row.at(x);
			if (sprite) {
			  sprite->Draw(CORNER_X + TILE_SIZE * x,
				       CORNER_Y + TILE_SIZE * y );
			  
			}
		}
     } 
}