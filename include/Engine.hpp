#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Heders.hpp"
#include "Leveling.hpp"
#include "Treasure.hpp"
#include "Renderer.hpp"
#include "Aabb.hpp"
#include "Writer.hpp"
#include "Lua.hpp"
#include "Entity.hpp"
#include "Sounder.hpp"

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
    void Load();
    void LoadLua(); 
    void SetScreen(SDL_Surface* Screen,ushort w,ushort h);    
    void NewGame();
    void NextLevel();
    void PlayLevel(ushort);
    
    static LuaPtr    GetLua() { return m_lua; }   
    ushort 	     GetScreenWidth() const { return m_screen_w;}
    ushort 	     GetScreenHeight() const {return m_screen_h; }
    SpriteConfigPtr  GetSpriteConfig() const { return m_SpriteConfig; }
    RendererPtr      GetRenderer() const { return m_Renderer; }
    SDL_Surface*     GetScreen() const { return m_screen; }
    AabbPtr 	     GetAabb() const{ return m_aabb; }
    WriterPtr        GetWriter() const { return m_Writer; }
    TreasurePtr	     GetTreasure() const { return m_treasure; }
    SpriteGrid*	     GetGrid()  { return &m_grid; }
    EntityFactoryPtr GetEntityFactory() const { return m_entity_factory; }
    LevelingPtr	     GetLeveling() const { return m_leveling; }
    SounderPtr	     GetSounder() const { return m_sound; }
    
private:
    //ustawienie poziomu poczatkowego gry
    Engine():m_level_of_game(1){}
  
    //Numer poziomu ktory jest aktualnie grany
    uint m_level_of_game;
  
    //Ustawienia globalne dla calej aplikacji, wczytywane z pliku
    static LuaPtr m_lua;
    
    //Informacje o polozeniu spritow w atlasie
    SpriteConfigPtr m_SpriteConfig;
    
    //Wskaznik do klasy obslugujacej wyswietlanie
    RendererPtr m_Renderer;
    
    //Klasa pozwalajaca wykryc kolizje miedzy obiektami
    AabbPtr m_aabb;
    
    //Klasa wypisujaca text na ekranie
    WriterPtr m_Writer;
    
    //Klasa przechowujaca rzeczy do zebrania na planszy
    TreasurePtr m_treasure;
    
    //Klasa wczytujaca ustawienia levelu z pliku
    LevelPtr m_level;
    
    //Klasa przechowujaca i rysujaca mape
    SpriteGrid m_grid;
    
    //Klasa przechowujaca przeciwnikow
    EntityFactoryPtr m_entity_factory;
    
    //Klasa zarzadzajaca levelami
    LevelingPtr m_leveling;
    
    // Klasa zarzadzajaca dzwiekiem
    SounderPtr m_sound;
    
    //Informacje o glownym Surface
    SDL_Surface* m_screen;
    ushort m_screen_h;
    ushort m_screen_w;
};


#endif
