#ifndef TREASURE_HPP
#define TREASURE_HPP
#include "Heders.hpp"
#include "SpriteGrid.hpp"

class Treasure{
public:
    Treasure(){};
    void CheckScore(const SDL_Rect&);    
    void SetGrid(SpriteGrid* Grid){ m_grid=Grid; }
    bool AddTreasure( const SDL_Rect& );
private:
    bool Contain(const SDL_Rect&);
    
    void PrintBox( const SDL_Rect& checkBox ){
        cout<<checkBox.x<<" : "<<checkBox.y<<" : "
            <<checkBox.w<<" : "<<checkBox.h<<endl;  
    }

    bool FindTreasure( const SDL_Rect& );
    SDL_Rect CollidesTreasure(const SDL_Rect& );
    
private: 
   SpriteGrid* m_grid;
   vector<SDL_Rect> m_treasure;
  
};
typedef boost::shared_ptr<Treasure> TreasurePtr;

#endif