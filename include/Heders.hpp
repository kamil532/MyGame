#ifndef HEDERS_HPP
#define HEDERS_HPP

#include <map>
#include <vector>
#include <list>
#include <SDL/SDL.h>
#include <boost/smart_ptr.hpp>
#include <boost/foreach.hpp>
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

#include "Consts.hpp"

inline void ShowBox( SDL_Rect& checkBox ){
        cout<<checkBox.x<<" : "<<checkBox.y<<" : "
            <<checkBox.w<<" : "<<checkBox.h<<endl;  
}


#endif 

 