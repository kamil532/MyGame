#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP
#include "Heders.hpp"
#include "Sprite.hpp"
#include "Engine.hpp"

class ProgressBar{
public:  
      ProgressBar(const SDL_Rect&,const SDL_Rect& );
  
  
private:
      bool m_empty;
      bool m_full;
      float m_width_bar;
      float m_width_uses;
      
      SpritePtr m_border;
      SpritePtr m_filling;      
};

typedef boost::shared_ptr<ProgressBar> ProgressBarPtr;

#endif