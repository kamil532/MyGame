#ifndef AABB_HPP
#define AABB_HPP
#include "Heders.hpp"

class Aabb{
public:
    explicit Aabb();     
    bool AddBox( SDL_Rect& );
    bool Collides(SDL_Rect& );
    bool IsOver( SDL_Rect& );
    bool IsUnder ( SDL_Rect& );
    bool IsOnLeftOf( SDL_Rect& );
    bool IsOnRightOf( SDL_Rect& );
    void PrintBox( SDL_Rect&);
    
    bool DEBUG;

private:
    bool Contain( const SDL_Rect&);    
    SDL_Rect CollidesBox( SDL_Rect& );   
  
private:
    vector<SDL_Rect> m_boxMap;
    
};
typedef boost::shared_ptr<Aabb> AabbPtr;

#endif