#include "Player.hpp"

Player::Player():m_x(PLAYER_X), m_y(PLAYER_Y),m_state(PS::Stand),m_vx(0.0f), 
m_vy(0.0f), m_running_factor(1.0f),m_live(1.0),m_live_dt(0.0),m_speed(1.0),
m_speed_dt(0.0){
m_x=PLAYER_X;
    m_sprites.insert(std::make_pair(PS::Stand,
                                    *(new SpritePtr(new Sprite("stand")))));

    m_sprites.insert(std::make_pair(PS::GoLeft,
                                    *(new SpritePtr(new Sprite("goLeft")))));

    m_sprites.insert(std::make_pair(PS::GoRight,
                                    *(new SpritePtr(new Sprite("goRight")))));

    m_sprites.insert(std::make_pair(PS::GoUp,
                                    *(new SpritePtr(new Sprite("goUp")))));

    m_sprites.insert(std::make_pair(PS::GoDown,
                                    *(new SpritePtr(new Sprite("goDown")))));
  
    SDL_Rect ProgressRamka={110,40,130,30};
    SDL_Rect ProgressWypelnienie={112,42,122,20};    
    m_progressBar.reset(new ProgressBar(ProgressRamka,ProgressWypelnienie));
    
    SDL_Rect SpeedRamka={310,40,130,30};
    SDL_Rect SpeedWypelnienie={312,42,122,20}; 
    m_speedBar.reset(new ProgressBar(SpeedRamka, SpeedWypelnienie));
    
   
}

void Player::CorectPos(float& next_x, float& next_y){
    //Funkcja zmienia polozenie postaci
    //tak aby latwiej bylo skrecic
    
    ushort margin_x= ( static_cast<int>(next_x-CORNER_X) ) % TILE_SIZE;
    ushort margin_y= ( static_cast<int>(next_y-CORNER_Y) ) % TILE_SIZE;

    ushort tile_x = next_x - margin_x;
    ushort tile_y = next_y - margin_y;

    SDL_Rect tmp={next_x, next_y, PLAYER_SIZE, PLAYER_SIZE};


    if ( m_state == PS::GoDown || m_state == PS::GoUp ) {

        if (  Engine::Get().GetAabb()->IsOver(tmp)) {
            SDL_Rect checker_ld={ tile_x+1, tile_y+TILE_SIZE+1, TILE_SIZE,TILE_SIZE };
            SDL_Rect checker_rd={ (tile_x + TILE_SIZE)+1, tile_y+TILE_SIZE+1, TILE_SIZE,TILE_SIZE };
            if ( !Engine::Get().GetAabb()->Collides(checker_rd)) {
                next_x= tile_x + TILE_SIZE + 1;
	    next_y=m_y;
            }

            if ( !Engine::Get().GetAabb()->Collides(checker_ld)) {
                next_x= tile_x + 1;
	       next_y=m_y;
            }
        }

        if ( Engine::Get().GetAabb()->IsUnder(tmp)) {
            SDL_Rect checker_lu={ tile_x+1, tile_y-TILE_SIZE+1, TILE_SIZE,TILE_SIZE };
            SDL_Rect checker_ru={ (tile_x + TILE_SIZE)+1, tile_y-TILE_SIZE+1, TILE_SIZE,TILE_SIZE };

            if ( !Engine::Get().GetAabb()->Collides(checker_ru)
                   ) {
                next_x= tile_x + TILE_SIZE + 1;
	       next_y=m_y;
            }

            if ( !Engine::Get().GetAabb()->Collides(checker_lu)
                   ) {
                next_x= tile_x + 1;
	       next_y=m_y;
            }
        }
    }

  if ( m_state == PS::GoRight || m_state == PS::GoLeft ) {
	
	    if (  Engine::Get().GetAabb()->IsOnLeftOf(tmp)){
	        SDL_Rect checker_ul={ tile_x + TILE_SIZE, tile_y+1, TILE_SIZE,TILE_SIZE };
	        SDL_Rect checker_dl={ tile_x + TILE_SIZE, tile_y+TILE_SIZE+1, TILE_SIZE, TILE_SIZE };
	      
	      if ( !Engine::Get().GetAabb()->Collides(checker_ul)
         
		 ) {
                next_y= tile_y + 1;
	      next_x=m_x;
            }
             if ( !Engine::Get().GetAabb()->Collides(checker_dl)

		 ) {
                next_y= tile_y + TILE_SIZE + 1;
	       next_x=m_x;
            }
	      
	    }
	    
	   if (  Engine::Get().GetAabb()->IsOnRightOf(tmp)){
		SDL_Rect checker_ur={ tile_x + TILE_SIZE, tile_y+1, TILE_SIZE,TILE_SIZE };
	        SDL_Rect checker_dr={ tile_x + TILE_SIZE, (tile_y+TILE_SIZE)+1, TILE_SIZE, TILE_SIZE };
		 
		     if ( !Engine::Get().GetAabb()->Collides(checker_ur)
		     ){
                next_y= tile_y + 1;
		  next_x=m_x;
            }
            
                 if ( !Engine::Get().GetAabb()->Collides(checker_dr)) {
                next_y= (tile_y + TILE_SIZE) + 1 ;
		  next_x=m_x;
            }
		  
	        }
      } 
}

void Player::Update(const double& dt) {
        
    //funckcja obliaczajaca nastepne wspolrzedne postaci
    float next_x=GetNextXPosition(dt);
    float next_y=GetNextYPosition(dt);

    //Funckcje wpsomaga skrecanie playera w sciezce
    CorectPos(next_x, next_y);
    
    //Kwadrat na ktorym sie miesci sprite gracza
    SDL_Rect tmp={next_x, next_y, PLAYER_SIZE, PLAYER_SIZE};
    
    
    //okreslenie w ktora strone sie porusza postac 
    //tak aby nie bylo ruchu w dwoch plaszczyznach jednoczesnie
    if ( next_x > m_x && Engine::Get().GetAabb()->IsOnRightOf(tmp)) {
        next_x=m_x;
    }
    if ( next_x < m_x && Engine::Get().GetAabb()->IsOnLeftOf(tmp)) {
        next_x=m_x;
    }
    if ( next_y > m_y && Engine::Get().GetAabb()->IsOver(tmp)) {
        next_y=m_y;
    }
    if ( next_y < m_y && Engine::Get().GetAabb()->IsUnder(tmp)) {
        next_y=m_y;
    }

  tmp.x=next_x+10; tmp.y=next_y+20; tmp.h-=20; tmp.w-=35; 
  ControlLive(tmp,dt);
  ControlSpeed(dt);


    //aktualizacja paskow 
    m_progressBar->Update(m_live); 
    m_speedBar->Update(m_speed);
        
    //zmiana pozycji postaci
    m_x = next_x;
    m_y = next_y;
       
   //aktualizacja sprita, ktory jest aktualnie 
   m_sprites.find(m_state)->second->Update( dt );
}


void Player::ControlSpeed(const double& dt){

    m_speed_dt+=dt;
    
    if(m_running_factor > 1 && m_speed < 0.1) StopRun();    

    if (m_speed_dt > 0.1 && m_running_factor > 1) {
        m_speed-=0.02;
        m_speed_dt-=0.05;
    }
    else if (m_speed_dt > 0.01 && m_running_factor == 1 ) {
        m_speed+=0.005;
        m_speed_dt-=0.01;
    }

    if (m_speed > 1.05) m_speed=1.05;
    else if (m_speed < 0) m_speed=0;
}

void Player::ControlLive(SDL_Rect& tmp ,const double& dt){
  
 m_live_dt+=dt;
 
    if (m_live_dt > 0.1) {
        m_live_dt-=0.1;
        if (m_live>= 0.005) m_live-=0.005;
    }

    //Sprawdzanie czy player nie odnalazl czegos

    if ( Engine::Get().GetTreasure()->CheckScore(tmp)) {
        if (m_live<=0.95) m_live+=0.1;
    }  
    
    if(m_live<0) m_live=0;
}

void Player::Draw() const {
    if (m_sprites.find(m_state) !=m_sprites.end()) ;
    else throw ("[Critical] Player state not found");
    m_sprites.find(m_state)->second->Draw( m_x, m_y );
    m_progressBar->Draw();   
    m_speedBar->Draw();
}

