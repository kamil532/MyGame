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

namespace GAMESPACE{
	using std::cout;
	using std::endl;
	using std::string;
	using std::vector;
	using std::fstream;
	using std::map;
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

#endif 

 
