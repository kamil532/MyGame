#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Heders.hpp"

class Level {
public:
    explicit Level():m_width(0), m_height(0) {};

    void LoadFromFile( const string& );
    FT::FieldType GetField(size_t, size_t ) const;
    
    ushort GetWidth()  const{ return m_width; }
    ushort GetHeight() const{ return m_height; }

private:
    ushort m_width;
    ushort m_height;
    std::vector<std::vector<FT::FieldType> > m_data;
};
typedef boost::shared_ptr<Level> LevelPtr;

#endif


