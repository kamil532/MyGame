#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Heders.hpp"
#include "Sprite.hpp"
#include "SpriteGrid.hpp"
#include "Engine.hpp"

class Player{
public:
    explicit Player();
    void Draw() const;
    void Update( double );  
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
    void StartRun(){ m_running_factor=1.5 ; }
    void StopRun(){ m_running_factor=1; }    
    void StopState();
    void SetGrid( SpriteGrid* Grid ){ m_grid=Grid; }

private:  
     float GetNextXPosition(double dt) const {
        return m_x + m_vx * dt * m_running_factor;
      }    
     float GetNextYPosition(double dt) const {
        return m_y + m_vy * dt * m_running_factor;
      }     
     void CorectPos(float& x, float& y);
     void IncreaseLive(double);
     void DecreaseLive();
     
private:  
      float m_x;
      float m_y;
      PS::PlayerState m_state;    
      float m_vx;
      float m_vy;
      float m_running_factor;
      
      SpritePtr m_live_border;
      
      SpritePtr m_live_background;
      double m_live_time;
      float m_live_mount;
      ushort m_live_width;
      short m_live_accumulator;
      
      
      SpriteGrid* m_grid; //adres obiektu nalezacego do engine  
      map<PS::PlayerState, SpritePtr > m_sprites;
};
typedef boost::shared_ptr<Player> PlayerPtr;

#endif