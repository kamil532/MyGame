#include "Treasure.hpp"
#include <Engine.hpp>

void Treasure::CheckScore( SDL_Rect& Box){
 bool find = false;
list_rec_it it_tmp = FindTreasure( Box , find );
 if (find){
    m_grid->DeleteGrid(CollidesTreasure(Box));
    ushort tmp = Engine::Get().GetWriter()->GetScore();
    Engine::Get().GetWriter()->SetScore( tmp + 100 );
    m_treasure.erase( it_tmp ); 
 }
    
}

bool Treasure::AddTreasure(const SDL_Rect& newBox ){
  //Dodaje nowy prostokat do tablicy skarbow
  if ( Contain( newBox ) ) return false;  
    m_treasure.push_back( newBox );   return true; 
}

bool Treasure::Contain(const SDL_Rect& Box){
   for ( list<SDL_Rect>::iterator it=m_treasure.begin();
        it!=m_treasure.end() ;
        ++it ){
         if (  it->x == Box.x
            && it->y == Box.y
            && it->h == Box.h
            && it->w == Box.w)  return true;
      } 
 return false;  
}

list_rec_it Treasure::FindTreasure( SDL_Rect& checkBox, bool& find ){
  list<SDL_Rect>::iterator it = m_treasure.begin();

  for (list_rec_it it=m_treasure.begin(); it!=m_treasure.end();++it)  
 {
        if (   (it->x) >= ( checkBox.x + checkBox.w )
                ||(it->x + it->w) <= ( checkBox.x)
                ||(it->y) >= ( checkBox.y + checkBox.h )
                ||(it->y + it->h) <= ( checkBox.y  )
           ){ continue; }
        else{ 
	  find = true;
	  return it;
	}
    }
    find = false;
    return it;
}

SDL_Rect Treasure::CollidesTreasure(const SDL_Rect& checkBox){

    BOOST_FOREACH(SDL_Rect it, m_treasure) {
        if (   (it.x) >= ( checkBox.x + checkBox.w )
                ||(it.x + it.w) <= ( checkBox.x)
                ||(it.y) >= ( checkBox.y + checkBox.h )
                ||(it.y + it.h) <= ( checkBox.y )
           ) continue;
        else return it;
    }  
    
   SDL_Rect _NULL_RECT={0,0,0,0}; 
   return  _NULL_RECT; 
}
