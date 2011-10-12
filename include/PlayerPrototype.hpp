#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP
#include "Heders.hpp"
#include "Engine.hpp"

/* Wzorzec projektowy prototyp ma tutaj na celu zmniejszyc ilosc kodu
 * w klasie player, tak zeby stala sie bardziej czytelna.
 * Klasa PlayerPrototype zawiera implemetacje prostych funkcji inline
 * ktore slusza do obslugi przemieszczenia postaci.
 * Sa one inline w klasie, wiec zajmowalyby niepotrzebnie miejscie w klasi PlayerPrototype
 * Ich implementacja inline jest bardzo wazna ze wzgledu na szybkosc silnika
 * gry. A pozostawianie ich cial w klasie zmniejszylo ilosc plikow projektu
 */


class PlayerPrototype{
public:
    void GoLeft() {
      if( m_state == PS::Stand || m_state == PS::GoLeft){    
        m_vx-=Engine::GetLua()->SPEED;
        m_state=PS::GoLeft;}
    }  
    void StopLeft() {
       if( m_state == PS::GoLeft){ 
        m_vx+=Engine::GetLua()->SPEED;
        m_state=PS::Stand;
      }
    }    
    void GoRight() {
      if( m_state == PS::Stand || m_state == PS::GoRight){
        m_vx+=Engine::GetLua()->SPEED;
        m_state=PS::GoRight;
      }
    }   
    void StopRight() {
       if( m_state == PS::GoRight){ 
        m_vx-=Engine::GetLua()->SPEED;
        m_state=PS::Stand;	 
      }
    }    
    void GoUp() {
     if( m_state == PS::Stand || m_state == PS::GoUp){
        m_vy-=Engine::GetLua()->SPEED;
        m_state=PS::GoUp;}
    }    
    void StopUp() {
      if( m_state == PS::GoUp){
        m_vy+=Engine::GetLua()->SPEED;
        m_state=PS::Stand;}
    }
    void GoDown() {
      if( m_state == PS::Stand || m_state == PS::GoDown){
        m_vy+=Engine::GetLua()->SPEED;
        m_state=PS::GoDown;}
      }  
    void StopDown() {
        if( m_state == PS::GoDown){
        m_vy-=Engine::GetLua()->SPEED;
        m_state=PS::Stand;}
    }
    void StartRun(){ m_running_factor= 1.5;} //magiczna liczba, zeby user nie mogl zmienic tej wartosci
    void StopRun(){ m_running_factor= 1; }      
    void StopState() {
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
        case ( PS::Stand ):
            break;
        }
    }

protected:  
     float GetNextXPosition(double dt) const {
        return m_x + m_vx * dt * m_running_factor;
      }    
     float GetNextYPosition(double dt) const {
        return m_y + m_vy * dt * m_running_factor;
      }  
      
     PlayerPrototype():m_x(Engine::GetLua()->PLAYER_X), 
		      m_y(Engine::GetLua()->PLAYER_Y), 
		      m_state(PS::Stand),m_vx(0.0f),
		      m_vy(0.0f),m_running_factor(1.0)
		      { /*Ustawienia poczatkowe player, 
		      pozycja, predkosci itd*/ }
		      
protected:
      float m_x;
      float m_y;
      PS::PlayerState m_state;    
      float m_vx;
      float m_vy;
      float m_running_factor;
};


#endif