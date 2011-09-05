#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "Heders.hpp"
#include "Treasure.hpp"
#include "Renderer.hpp"
#include "Aabb.hpp"
#include "Writer.hpp"

/* Klasa singleton, dzieki ktorej uzuskuje sie dostep do
 * klas, ktore rowniez powinny miec tylko jedna instacje.
 * Wazna jest tutaj klasa renderer, ktora posiada funkcje rysujace
 * funkcje te sa przeznaczone dla innych klas, ktore nie maja 
 * prawa rysowac po ekranie bezposrednio (Jezeli jakas klasa tak robi,
 * to jest to blad. Pozostalosc po testowaniu pewnych modulow ).
 * Funckcja Load musi zostac uzyta przed uzyciem jakiegolwiek funkcji
 * z suffiksem Get, bo tworzy ona wszystkie obiekty
 */ 

class Engine {
public:
 static Engine& Get() {
        static Engine engine;
        return engine;
    }
    
public:  
    void Load() {
    m_SpriteConfig.reset( new SpriteConfig() );
    m_Renderer.reset( new Renderer( m_screen , ATLAS_PATH) );
    m_aabb.reset( new Aabb() );
    m_Writer.reset( new Writer() );
    m_treasure.reset( new Treasure ); 
  
    m_level.reset(new Level());
    m_level->LoadFromFile("data/1.lvl");

    m_grid.StoreSprite(FT::PlatformLeftEnd,  SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_left"))));
    m_grid.StoreSprite(FT::PlatformMidPart,  SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_mid"))));
    m_grid.StoreSprite(FT::PlatformRightEnd, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_right"))));
    m_grid.StoreSprite(FT::Fruit, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("fruit"))));
    m_grid.SetLevel(m_level);
	
    }

    void SetScreen(SDL_Surface* Screen,ushort w,ushort h) { 
			m_screen = Screen;
			m_screen_h = h;
			m_screen_w = w;
    }
    
    ushort 	    GetScreenWidth() const { return m_screen_w;}
    ushort 	    GetScreenHeight() const {return m_screen_h; }
    SpriteConfigPtr GetSpriteConfig() const { return m_SpriteConfig; }
    RendererPtr     GetRenderer() const { return m_Renderer; }
    SDL_Surface*    GetScreen() const { return m_screen; }
    AabbPtr 	    GetAabb() const{ return m_aabb; }
    WriterPtr       GetWriter() const { return m_Writer; }
    TreasurePtr	    GetTreasure() const { return m_treasure; }
    SpriteGrid*	    GetGrid()  { return &m_grid; }
    
private:
    SpriteConfigPtr m_SpriteConfig;
    RendererPtr m_Renderer;
    AabbPtr m_aabb;
    WriterPtr m_Writer;
    TreasurePtr m_treasure;
    LevelPtr m_level;
    SpriteGrid m_grid;
    
    // Informacje o glownym Surface
    SDL_Surface* m_screen;
    ushort m_screen_h;
    ushort m_screen_w;
  };

#endif
