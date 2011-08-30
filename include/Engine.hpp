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

    void SetScreen(SDL_Surface* Screen) { m_screen=Screen; }
    
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
};

#endif
