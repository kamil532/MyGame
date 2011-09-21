#include "Level.hpp"

void Level::LoadFromFile( const string& FileName){

  std::ifstream lvl(FileName.c_str());
  
  if (!lvl) throw("[Critical] Brak pliku levelu: "+ FileName);
      
    lvl >> m_width >> m_height;
    m_data.resize(m_height);
    
     for (size_t y = 0; y < m_height; ++y) {
        m_data.at(y).resize(m_width);
    }
    
    int tmp;
    for (size_t y = 0; y < m_height; ++y) {
        for (size_t x = 0; x < m_width; ++x) {
            lvl >> tmp;
            m_data.at(y).at(x) = FT::FieldType(tmp);
        }
    }
    
  int EntityAmount=0;  
  lvl>> EntityAmount;
  
  
  for (ushort i=0; i<EntityAmount; ++i){
    ushort x=0,y=0;
    string name;
    lvl>>x>>y>>name;
   ( m_entityF )->AddEntity(x,y,name);
  }  
    
}


FT::FieldType Level::GetField(size_t x, size_t y) const {
    if (x >= m_width || y >= m_height) {
        return FT::None;
    }
    return m_data.at(y).at(x);
}