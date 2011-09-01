#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "Heders.hpp"
#include "Treasure.hpp"
#include "Renderer.hpp"
#include "Aabb.hpp"
#include "Writer.hpp"


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
    
private:
    SpriteConfigPtr m_SpriteConfig;
    RendererPtr m_Renderer;
    AabbPtr m_aabb;
    WriterPtr m_Writer;
    TreasurePtr m_treasure;
    
    SDL_Surface* m_screen;
    ushort m_screen_h;
    ushort m_screen_w;
  };

#endif
