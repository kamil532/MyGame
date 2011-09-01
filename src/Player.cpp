#include "Player.hpp"

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

void Player::Update(double dt) {
        
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

  //Sprawdzanie czy player nie odnalazl czegos
  tmp.x=next_x+10; tmp.y=next_y+20; tmp.h-=20; tmp.w-=35;
  Engine::Get().GetTreasure()->CheckScore(tmp);

  //zmiana pozycji postaci
    m_x = next_x;
    m_y = next_y;
    
    IncreaseLive(dt);
    
   //aktualizacja sprita, ktory jest aktualnie 
   m_sprites.find(m_state)->second->Update( dt );
}

Player::Player():m_x(PLAYER_X), m_y(PLAYER_Y),m_state(PS::Stand),
        m_vx(0.0f), m_vy(0.0f), m_running_factor(1.0f),
        m_live_mount(1), m_live_width(120),m_live_accumulator(0){

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
  
   m_live_border.reset(new Sprite("livebar",
	0.1 * Engine::Get().GetScreenWidth(), 40 )); 
   
   m_live_background.reset(new Sprite("livebarback",
	0.1 * Engine::Get().GetScreenWidth() + 5, 40 ));
    
   m_live_background->SetWidth( m_live_width);
   
}

void Player::Draw() const {
    if (m_sprites.find(m_state) !=m_sprites.end()) ;
    else throw ("[Critical] Player state not found");
    m_sprites.find(m_state)->second->Draw( m_x, m_y );
    
    //rysowanie ramki livebaru i wypelnienia
    //wypelnienie okreslone na podstawie ilosci zycia
    m_live_background->Draw();  
    m_live_border->Draw();    
}

void Player::StopState() {
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

void Player::IncreaseLive(double Time){
 
  m_live_time+=Time;
  
  if( m_live_time > 0.9 && m_live_mount >= 0.05 ) {
    m_live_time-=0.9;
    m_live_mount-=0.01; 
    m_live_accumulator += m_live_width - (m_live_width * m_live_mount);    

  }
  
      if(m_live_accumulator > 0){
      --m_live_accumulator;
      --m_live_width;      
      m_live_background->SetWidth( m_live_width);
    } 
    
  
    
}

void Player::DecreaseLive(){
  
  
}