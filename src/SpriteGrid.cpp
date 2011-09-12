#include "SpriteGrid.hpp"
#include "Engine.hpp"

SpriteGrid::SpriteGrid():m_level_height(0),m_level_width(0),
 m_background( IMG_Load("data/tex.bmp"))
{ 	  
  if( m_background == NULL ) std::cerr<< "[ERROR] No background found\n";	}

void SpriteGrid::StoreSprite(FT::FieldType ft, SpritePtr Sprite){
  //dodawanie sprite do bazy danych tej klasy
  if ((m_sprites.size() <= static_cast<size_t> (ft)))  
			    m_sprites.resize(ft + 1);
  m_sprites.at(ft) = Sprite;  
}

void SpriteGrid::DeleteGrid(SDL_Rect Rect){
    int x=(Rect.x-Engine::GetLua()->CORNER_X)/Engine::GetLua()->TILE_SIZE;
	  int y=(Rect.y-Engine::GetLua()->CORNER_Y)/Engine::GetLua()->TILE_SIZE;
	 if(x>=0 && y>=0)
	  m_grid.at(y).at(x).reset();     
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
		SDL_Rect tmp={Engine::GetLua()->CORNER_X + Engine::GetLua()->TILE_SIZE * x,
			      Engine::GetLua()->CORNER_X + Engine::GetLua()->TILE_SIZE * y,
			      Engine::GetLua()->TILE_SIZE*2,Engine::GetLua()->TILE_SIZE*2};
			      
			      Engine::Get().GetTreasure()->AddTreasure(tmp);
	      }
		
		
	      
	  }
     }
   
     for (size_t y = 0; y < m_grid.size(); ++y) {
            const std::vector<SpritePtr>& row = m_grid.at(y);
		for (size_t x = 0; x < row.size(); ++x) {
		  const SpritePtr& sprite = row.at(x);
		  if(sprite){		
			  sprite->SetX(Engine::GetLua()->CORNER_X + Engine::GetLua()->TILE_SIZE * x);
			  sprite->SetY(Engine::GetLua()->CORNER_X + Engine::GetLua()->TILE_SIZE * y);
			  SDL_Rect tmp;
			  tmp.x = sprite->GetX();
			  tmp.y = sprite->GetY();
			  tmp.h = Engine::GetLua()->TILE_SIZE;
			  tmp.w = Engine::GetLua()->TILE_SIZE;
			  
			  if(sprite->GetType() < 4 ) //![ilosc elementow mapy]
			  Engine::Get().GetAabb()->AddBox(tmp);
		  }
		}
     } 
     
}

void SpriteGrid::Draw() const{

//Engine::Get().GetRenderer()->Draw(m_background);
  
     for (size_t y = 0; y < m_grid.size(); ++y) {
            const std::vector<SpritePtr>& row = m_grid.at(y);
		for (size_t x = 0; x < row.size(); ++x) {
		  const SpritePtr& sprite = row.at(x);
			if (sprite) {
			  sprite->Draw(Engine::GetLua()->CORNER_X + Engine::GetLua()->TILE_SIZE * x,
				       Engine::GetLua()->CORNER_Y + Engine::GetLua()->TILE_SIZE * y );
			  
			}
		}
     } 
}