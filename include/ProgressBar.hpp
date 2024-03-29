#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP
#include "Heders.hpp"
#include "Sprite.hpp"

class ProgressBar{
public:  
      ProgressBar( const SDL_Rect&,const SDL_Rect& );
      void Update( const double& );
      void Draw() const;
      bool LessThen(const double&) const;
      
private:
      bool m_empty;
      bool m_full;
      double m_width_bar;
      double m_width_uses;
      const float m_long_bar;
      
      SpritePtr m_border;
      SpritePtr m_filling;     
};

typedef boost::shared_ptr<ProgressBar> ProgressBarPtr;

#endif