#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Heders.hpp"
#include "Sprite.hpp"
#include "SpriteGrid.hpp"
#include "Engine.hpp"
#include "ProgressBar.hpp"
#include "PlayerPrototype.hpp"


class Player: public PlayerPrototype{
public:
    explicit Player();   
    void Draw() const;
    void Update(const double& );    
    void SetGrid( SpriteGrid* Grid ){ m_grid=Grid; }
    static void AddScore(const ulong& Score){
      m_score+=Score;      
    }

private:         
     void CorectPos(float& x, float& y);
     void ControlSpeed(const double&);
     void ControlLive(SDL_Rect&,const double&);
     
private:  
     ProgressBarPtr m_progressBar;  
     double m_live;
     double m_live_dt;
      
     ProgressBarPtr m_speedBar;
     double m_speed;
     double m_speed_dt;
      
     SpriteGrid* m_grid; //adres obiektu nalezacego do engine  
     map<PS::PlayerState, SpritePtr > m_sprites;
     
     static ulong m_score;
     SDL_Rect m_score_rect;
  
};
typedef boost::shared_ptr<Player> PlayerPtr;

#endif