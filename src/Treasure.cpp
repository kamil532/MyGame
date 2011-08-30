#include "Treasure.hpp"

void Treasure::CheckScore(const SDL_Rect& Box){
   //m_grid-> DeleteGrid((Engine::Get().GetAabb()->CollidesTreasure(tmp)));
PrintBox(Box);
  if( FindTreasure(Box)){
    m_grid->DeleteGrid(CollidesTreasure(Box));
  };
  
}

bool Treasure::AddTreasure(const SDL_Rect& newBox ){
  //Dodaje nowy prostokat do tablicy skarbow
  if ( Contain( newBox ) ) return false;  
    m_treasure.push_back( newBox );    
}

bool Treasure::Contain(const SDL_Rect& Box){
   for ( vector<SDL_Rect>::iterator it=m_treasure.begin();
        it!=m_treasure.end() ;
        ++it ){
         if (  it->x == Box.x
            && it->y == Box.y
            && it->h == Box.h
            && it->w == Box.w)  return true;
      } 
 return false;  
}

bool Treasure::FindTreasure(const SDL_Rect& checkBox){
  vector<SDL_Rect>::iterator it = m_treasure.begin();

    BOOST_FOREACH(SDL_Rect it, m_treasure) {
        if (   (it.x) >= ( checkBox.x + checkBox.w )
                ||(it.x + it.w) <= ( checkBox.x)
                ||(it.y) >= ( checkBox.y + checkBox.h )
                ||(it.y + it.h) <= ( checkBox.y  )
           ){ continue; }
        else{ 
	  return true;
	}
    }

    return false; 
}

SDL_Rect Treasure::CollidesTreasure(const SDL_Rect& checkBox){
  vector<SDL_Rect>::iterator it = m_treasure.begin();

    BOOST_FOREACH(SDL_Rect it, m_treasure) {
        if (   (it.x) >= ( checkBox.x + checkBox.w )
                ||(it.x + it.w) <= ( checkBox.x)
                ||(it.y) >= ( checkBox.y + checkBox.h )
                ||(it.y + it.h) <= ( checkBox.y )
           ) continue;
        else return it;
    }  
}
