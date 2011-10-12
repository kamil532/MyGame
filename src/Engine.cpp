#include "Engine.hpp"
#include "Lua.hpp"

LuaPtr Engine::m_lua;

void Engine::PlayLevel(ushort Lp){
  m_level_of_game=Lp-1;
  NextLevel();  
}

void Engine::NextLevel(){
  ++m_level_of_game;
  
    m_entity_factory.reset(new EntityFactory());
    m_aabb.reset( new Aabb() );
    m_treasure.reset( new Treasure );    
    m_entity_factory.reset(new EntityFactory());
    m_level.reset(new Level( m_entity_factory.get()) );
    
    string Text("data/");
    std::ostringstream ss;
    ss << m_level_of_game;
    Text+=ss.str();
    Text+=".lvl";
  
    m_level->LoadFromFile(Text.c_str());

    m_grid=*(new SpriteGrid()); 
    m_grid.StoreSprite(FT::PlatformLeft,  SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_left"))));
    m_grid.StoreSprite(FT::PlatformDown,  SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_down"))));
    m_grid.StoreSprite(FT::PlatformUp, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_up"))));
    m_grid.StoreSprite(FT::PlatformRight, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_right"))));
    m_grid.StoreSprite(FT::PlatformHorizontal, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_h"))));
    m_grid.StoreSprite(FT::PlatformVertical, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_v"))));
    m_grid.StoreSprite(FT::Coin, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("coin"))));
    m_grid.SetLevel(m_level);
    
   GetTreasure()->SetGrid( GetGrid() );  
}

void Engine::NewGame(){  
  m_level_of_game=0; 
  NextLevel();
}

void Engine::Load() {
   // Resetowanie shared_ptr-ow
    m_SpriteConfig.reset( new SpriteConfig() );
    m_Renderer.reset( new Renderer( m_screen ,Engine::GetLua()->ATLAS_PATH) );
    m_aabb.reset( new Aabb() );
    m_Writer.reset( new Writer() );
    m_lua->LoadSpriteData();
    m_treasure.reset( new Treasure );
    m_leveling.reset( new Leveling() );  
    m_entity_factory.reset(new EntityFactory());
    m_sound.reset( new Sounder() );
}

void Engine::SetScreen(SDL_Surface* Screen,ushort w,ushort h) {
    m_screen = Screen;
    m_screen_h = h;
    m_screen_w = w;
}

void Engine::LoadLua(){
      LuaLoader m_lua_loader(*( new string( "config.lua" )) );
      m_lua.reset(new Lua(m_lua_loader.GetLuaData() ));
}




