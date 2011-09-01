#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP
#include "Heders.hpp"
#include "Sprite.hpp"
#include "Engine.hpp"

class ProgressBar{
public:  
      ProgressBar( const SDL_Rect&,const SDL_Rect& );
      void Update( const float& );
      void Draw() const;
private:
      bool m_empty;
      bool m_full;
      float m_width_bar;
      float m_width_uses;
      const float m_long_bar;
      
      SpritePtr m_border;
      SpritePtr m_filling;
      
};

typedef boost::shared_ptr<ProgressBar> ProgressBarPtr;

#endif