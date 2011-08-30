#include "Aabb.hpp"
#include <stdlib.h>

Aabb::Aabb():DEBUG(false){}

void Aabb::PrintBox( SDL_Rect& checkBox ){
        cout<<checkBox.x<<" : "<<checkBox.y<<" : "
            <<checkBox.w<<" : "<<checkBox.h<<endl;  
}

bool Aabb::AddBox( SDL_Rect& newBox ){  
    if ( Contain( newBox ) ) return false;  
    m_boxMap.push_back( newBox );  
}


bool Aabb::Contain( const SDL_Rect& Box){

  for ( vector<SDL_Rect>::iterator it=m_boxMap.begin();
        it!=m_boxMap.end() ;
        ++it ){
         if (  it->x == Box.x
            && it->y == Box.y
            && it->h == Box.h
            && it->w == Box.w)  return true;
      } 
 return false;
}

bool Aabb::Collides( SDL_Rect& checkBox ){

    vector<SDL_Rect>::iterator it = m_boxMap.begin();

    BOOST_FOREACH(SDL_Rect it, m_boxMap) {
        if (   (it.x) > ( checkBox.x + checkBox.w )
                ||(it.x + it.w) < ( checkBox.x)
                ||(it.y) > ( checkBox.y + checkBox.h )
                ||(it.y + it.h) < ( checkBox.y )
           ) continue;
        else return true;
    }

    return false;
}


SDL_Rect Aabb::CollidesBox( SDL_Rect& checkBox ){
  vector<SDL_Rect>::iterator it = m_boxMap.begin();

    BOOST_FOREACH(SDL_Rect it, m_boxMap) {
        if (   (it.x) >= ( checkBox.x + checkBox.w )
                ||(it.x + it.w) <= ( checkBox.x)
                ||(it.y) >= ( checkBox.y + checkBox.h )
                ||(it.y + it.h) <= ( checkBox.y )
           ) continue;
        else return it;
    }
}


bool Aabb::IsOver( SDL_Rect& checkBox ){
  SDL_Rect tmp=CollidesBox( checkBox );
  
  if (DEBUG){
    PrintBox( checkBox );
    PrintBox( tmp );    
  }
  
  return Collides(checkBox)
	 && tmp.y < (checkBox.y + checkBox.h)
	 && (checkBox.y + checkBox.h) < (tmp.y + tmp.h);
}

bool Aabb::IsOnLeftOf ( SDL_Rect& checkBox){
   SDL_Rect tmp=CollidesBox( checkBox );
   
    if (DEBUG){
    PrintBox( checkBox );
    PrintBox( tmp );    
   } 
   
   return Collides(checkBox) 
	  && tmp.x < checkBox.x 
	  && checkBox.x < ( tmp.x + tmp.w );  
}

bool Aabb::IsOnRightOf ( SDL_Rect& checkBox){
  SDL_Rect tmp=CollidesBox( checkBox );
  
   if (DEBUG){
    PrintBox( checkBox );
    PrintBox( tmp );    
  }
  
  return Collides(checkBox) 
	  && tmp.x < ( checkBox.x + checkBox.w)
	  && ( checkBox.x + checkBox.w) < ( tmp.x + tmp.w ); 
}

bool Aabb::IsUnder( SDL_Rect& checkBox ){
  SDL_Rect tmp=checkBox;
  SDL_Rect checkbox=CollidesBox( tmp );
  
   if (DEBUG){
    PrintBox( checkBox );
    PrintBox( tmp );    
  }
  
  return Collides(checkbox)
	 && tmp.y < (checkbox.y + checkbox.h)
	 && (checkbox.y + checkbox.h) < (tmp.y + tmp.h);
 
}

