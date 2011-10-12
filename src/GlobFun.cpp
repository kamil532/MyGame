#include "Heders.hpp"

inline void ShowBox( SDL_Rect& checkBox ){
        std::cout<<checkBox.x<<" : "<<checkBox.y<<" : "
                 <<checkBox.w<<" : "<<checkBox.h<<std::endl;  
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

inline bool EqualRect(const SDL_Rect& A, const SDL_Rect& B){
  if(    A.x == B.x
      && A.y == B.y
      && A.h == B.h
      && A.w == B.w ) return true;
  else return false; 
}

template <typename Typ> 
Typ  Lua_cast( lua_State* lua,string& Name){  
return luabind::object_cast<Typ>(luabind::globals(lua)[Name.c_str()]);
}













