#ifndef HEDERS_HPP
#define HEDERS_HPP

/* Plik dolacza do projektu pliki bibliotek
 * oraz zawiera enumeratory uzywany w klasach
 * Dolacza plik Consts.hpp zawiera zmienne globalne 
 * uzywane w miejscu liczb magicznych 
 *
 * Tutaj znajduja sie naglowki funkcji globalnych (badz tez ich ciala) */

#include <map>
#include <vector>
#include <list>
#include <boost/smart_ptr.hpp>
#include <boost/foreach.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace GAMESPACE{
	using std::cout;
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
        PlatformLeftEnd = 1,
        PlatformMidPart = 2,
        PlatformRightEnd = 3,
	Fruit = 4,
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
    PlayMenu,
    Play    
  };  
}

#include "Consts.hpp"

inline void ShowBox( SDL_Rect& checkBox ){
        cout<<checkBox.x<<" : "<<checkBox.y<<" : "
            <<checkBox.w<<" : "<<checkBox.h<<endl;  
}

inline SDL_Surface* CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display)
{
  // 'display' is the surface whose format you want to match
  //  if this is really the display format, then use the surface returned from SDL_SetVideoMode

  const SDL_PixelFormat& fmt = *(display->format);
  return SDL_CreateRGBSurface(flags,width,height,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}

#endif 

 
