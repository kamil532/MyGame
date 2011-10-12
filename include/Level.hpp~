#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Heders.hpp"
#include "Entity.hpp"

class Level {
public:
    explicit Level(EntityFactory* Factory):
    m_width(0), m_height(0){
       m_entityF= Factory ;
    };

    void LoadFromFile( const string& );
    FT::FieldType GetField(size_t, size_t ) const;
    
    ushort GetWidth()  const{ return m_width; }
    ushort GetHeight() const{ return m_height; }

private:
    ushort m_width;
    ushort m_height;
    std::vector<std::vector<FT::FieldType> > m_data;
    EntityFactory* m_entityF;
    
};
typedef boost::shared_ptr<Level> LevelPtr;

#endif


