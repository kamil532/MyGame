#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Heders.hpp"
#include "Sprite.hpp"
#include "SpriteGrid.hpp"
#include "Engine.hpp"
#include "ProgressBar.hpp"

class Player{
public:
    explicit Player();
    
    void Draw() const;
    void Update(const double& );  
    void GoLeft() {
      if( m_state == PS::Stand || m_state == PS::GoLeft){    
        m_vx-=SPEED;
        m_state=PS::GoLeft;}
    }    
    void StopLeft() {
       if( m_state == PS::GoLeft){ 
        m_vx+=SPEED;
        m_state=PS::Stand;
      }
    }    
    void GoRight() {
      if( m_state == PS::Stand || m_state == PS::GoRight){
        m_vx+=SPEED;
        m_state=PS::GoRight;
      }
    }   
    void StopRight() {
       if( m_state == PS::GoRight){ 
        m_vx-=SPEED;
        m_state=PS::Stand;	 
      }
    }    
    void GoUp() {
     if( m_state == PS::Stand || m_state == PS::GoUp){
        m_vy-=SPEED;
        m_state=PS::GoUp;}
    }    
    void StopUp() {
      if( m_state == PS::GoUp){
        m_vy+=SPEED;
        m_state=PS::Stand;}
    }
    void GoDown() {
  if( m_state == PS::Stand || m_state == PS::GoDown){
        m_vy+=SPEED;
        m_state=PS::GoDown;}
    }  
    void StopDown() {
        if( m_state == PS::GoDown){
        m_vy-=SPEED;
        m_state=PS::Stand;}
    }
    void StartRun(){m_running_factor= 2 ; }
    void StopRun(){ m_running_factor= 1; }    
    void SetGrid( SpriteGrid* Grid ){ m_grid=Grid; }
    void StopState(){
      //znajduje aktualny stan postaci i wylacza go
    switch (m_state) {
    case ( PS::GoLeft ):
        StopLeft();
        break;
    case ( PS::GoRight ):
        StopRight();
        break;
    case ( PS::GoUp ):
        StopUp();
        break;
    case ( PS::GoDown ):
        StopDown();
        break;	
    case ( PS::Stand ): break;
      }   
  }

private:  
     float GetNextXPosition(double dt) const {
        return m_x + m_vx * dt * m_running_factor;
      }    
     float GetNextYPosition(double dt) const {
        return m_y + m_vy * dt * m_running_factor;
      }     
     void CorectPos(float& x, float& y);
     void ControlSpeed(const double&);
     void ControlLive(SDL_Rect&,const double&);
     
private:  
      float m_x;
      float m_y;
      PS::PlayerState m_state;    
      float m_vx;
      float m_vy;
      float m_running_factor;
      
      ProgressBarPtr m_progressBar;  
      double m_live;
      double m_live_dt;
      
      ProgressBarPtr m_speedBar;
      double m_speed;
      double m_speed_dt;
      
      SpriteGrid* m_grid; //adres obiektu nalezacego do engine  
      map<PS::PlayerState, SpritePtr > m_sprites;
};
typedef boost::shared_ptr<Player> PlayerPtr;

#endif