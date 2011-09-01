#ifndef WRITER_HPP
#define WRITER_HPP
#include "Heders.hpp"


class Writer{
public: 
  Writer(void);
  void Render(void);
  void SetScore(ulong Number);
  ulong GetScore(void) const {return m_score;}
  
private: 
  TTF_Font *m_font_a;
  
  SDL_Surface* m_score_surface;
  string m_score_string;
  SDL_Rect m_score_rect;
  SDL_Color m_font_color;
  ushort m_screen_height;
  ushort m_screen_width;  
  ulong m_score;
};
typedef boost::shared_ptr<Writer> WriterPtr;

#endif
