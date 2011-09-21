#ifndef SPRITEGRID_HPP
#define SPRITEGRID_HPP
#include "Heders.hpp"
#include "Level.hpp"
#include "Sprite.hpp"


class SpriteGrid{
public:
    explicit SpriteGrid();
    void SetLevel( LevelPtr );
    void Draw() const;
    void StoreSprite(FT::FieldType, SpritePtr);
    
    void DeleteGrid(SDL_Rect Rect);  
    
    FT::FieldType GetType(SDL_Rect&);
    
private:
   void SetSprite(size_t x,size_t y,SpritePtr sprite, FT::FieldType Ft){
        m_grid.at(y).at(x) = sprite;
	m_grid[y][x]->SetType(Ft);;
    }
    
private:
    ushort m_level_height;
    ushort m_level_width;    

    std::vector<SpritePtr> m_sprites;  
    std::vector< std::vector< SpritePtr > > m_grid;
    LevelPtr m_level;
    

};

#endif