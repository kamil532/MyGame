#ifndef HEDERS_HPP
#define HEDERS_HPP

/* Plik dolacza do projektu pliki bibliotek
 * oraz zawiera enumeratory uzywany w klasach
 * Dolacza plik Consts.hpp zawiera zmienne globalne 
 * uzywane w miejscu liczb magicznych 
 *
 * Tutaj znajduja sie naglowki funkcji globalnych */

#include <map>
#include <vector>
#include <list>

#include <boost/smart_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/random.hpp>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <luabind/luabind.hpp>
#include <lua.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <ctime>

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

namespace GAMESPACE{
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::string;
	using std::vector;
	using std::fstream;
	using std::map;
	using std::list;
	
	typedef list<SDL_Rect>::iterator list_rec_it;
	typedef vector<SDL_Rect>::iterator vec_rec_it;
}
using namespace GAMESPACE;

namespace FT {
    enum FieldType {
        None = 0,
        PlatformLeft = 1,
        PlatformUp = 2,
        PlatformRight = 3,
	PlatformDown = 4,
	PlatformVertical = 5,
	PlatformHorizontal= 6,
	Coin = 7,
        COUNT
    };
}

namespace PS {
    enum PlayerState {
        Stand,
        GoLeft,
        GoRight,
        GoUp,
	GoDown
    };
}

namespace GS{
  enum GameState{
    MainMenu,
    Play,
    NewGame,
    About,
    SelectLevel
  };  
}

namespace ES{
  enum EntityState{
    Up=0,
    Right,
    Down,
    Left   
  };
  
  
}

//Naglowki funkcji globalnych, ktore sa umieszczone w pliku GlobFun.cpp
inline void ShowBox( SDL_Rect& checkBox ); //Drukuje polozenie SDL_Rect
inline SDL_Surface* CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display);
inline bool EqualRect(const SDL_Rect& A, const SDL_Rect& B); //Porownuje dwa obiekty SDL_Rect
template <typename Typ> Typ Lua_cast( lua_State*, string&); //Rzutowanie na podany typ


#endif 

 
