#ifndef TREASURE_HPP
#define TREASURE_HPP
#include "Heders.hpp"
#include "SpriteGrid.hpp"

class Treasure{
public:
    Treasure():m_grid(NULL){};
    bool CheckScore( SDL_Rect&);    
    void SetGrid(SpriteGrid* Grid){ m_grid=Grid; }
    bool AddTreasure( const SDL_Rect& );
private:
    bool Contain(const SDL_Rect&);

    list_rec_it FindTreasure(  SDL_Rect&, bool& );
    SDL_Rect CollidesTreasure(const SDL_Rect& );
    
private: 
   SpriteGrid* m_grid;
   list<SDL_Rect> m_treasure;
  
};
typedef boost::shared_ptr<Treasure> TreasurePtr;

#endif