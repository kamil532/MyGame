#ifndef LUA_HPP
#define LUA_HPP
#include "Heders.hpp"
#include "SpriteConfig.hpp"

struct LuaData {
    string ATLAS_PATH;
    string APP_TITLE;
    string INFO;
    string FONT_PATH;
    string INTRO_PATH;
    float  TIME_STEP;
    float SPEED;
    double PLAYER_X;
    double PLAYER_Y;
    ushort PLAYER_SIZE;    
    ushort CORNER_X;
    ushort CORNER_Y;
    ushort TILE_SIZE;
    ushort INTRO_TIME;
    ushort RUN_FACTOR;
    ushort FONT_SIZE;
    bool FULL_SCREEN; 
    bool IMAGINATION;
    ushort LEVEL_MOUNT;
};

class LuaLoader{
public:  
  LuaLoader(string& LuaFilePath);
  LuaData& GetLuaData() { return m_lua_data; }
  
private:
  LuaData m_lua_data; 
};

class Lua{
public:  
    Lua( LuaData& );
    void LoadSpriteData();   
    const string INFO;
    const string ATLAS_PATH;
    const string APP_TITLE;
    const string FONT_PATH;
    const string INTRO_PATH;
    const float  TIME_STEP;
    const float SPEED;
    const double PLAYER_X;
    const double PLAYER_Y;
    const ushort PLAYER_SIZE;
    const ushort CORNER_X;
    const ushort CORNER_Y;
    const ushort TILE_SIZE;
    const ushort INTRO_TIME;
    const ushort RUN_FACTOR;
    const ushort FONT_SIZE;
    const bool FULL_SCREEN;
    const bool IMAGINATION;
    const ushort LEVEL_MOUNT;
  
};
typedef boost::shared_ptr<Lua> LuaPtr;

#endif