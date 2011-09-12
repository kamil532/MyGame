#include "Entity.hpp"
#include "Engine.hpp"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/typeof/typeof.hpp> 

boost::mt19937 gen;
int roll_die() {
    //zakres losowania lizb
    boost::uniform_int<> dist(1, 4);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
    return die();
}

Entity::Entity(const ushort& X, const ushort& Y,const string& Name):
m_vx(0), m_vy(0),m_state(ES::Left)
{
   m_x = Engine::Get().GetLua()->CORNER_X - 
         Engine::Get().GetLua()->TILE_SIZE +
	 Engine::Get().GetLua()->TILE_SIZE * X-2;
	 
   m_y = Engine::Get().GetLua()->CORNER_Y -
	 Engine::Get().GetLua()->TILE_SIZE+
	 Engine::Get().GetLua()->TILE_SIZE * Y+2;	 
	 
   m_sprite.reset(new Sprite(Name)); 	   
	 
}

void Entity::Update(const double& dt){
  
    switch (m_state){
      case (ES::Up):{
	m_vx=0;
	m_vy=Engine::Get().GetLua()->SPEED;
	  break;
      }
       case (ES::Down):{
	m_vx=0;
	m_vy=-Engine::Get().GetLua()->SPEED;
	break;
       }	
       case (ES::Left):{
	m_vx=-Engine::Get().GetLua()->SPEED;
	m_vy=0;
	break;
      }
       case (ES::Right):{
	m_vx=Engine::Get().GetLua()->SPEED;
	m_vy=0;
	break;
      }      
    }
    
  double next_x=NextXPosition(dt);
  double next_y=NextYPosition(dt);
    
  SDL_Rect posRect={next_x,next_y,
		    Engine::Get().GetLua()->PLAYER_SIZE,
		    Engine::Get().GetLua()->PLAYER_SIZE };
		    
		     SDL_Rect& tmp=posRect;
  
  if(Engine::Get().GetAabb()->Collides(posRect)){
    
        if ( next_x > m_x && Engine::Get().GetAabb()->IsOnRightOf(tmp)){
            SearchWay( next_x,next_y );
	    next_x=m_x;
        }
         else if ( next_y < m_y && Engine::Get().GetAabb()->IsUnder(tmp)){
            SearchWay( next_x,next_y );
	    next_y=m_y;
        }  
        else if ( next_x < m_x && Engine::Get().GetAabb()->IsOnLeftOf(tmp)){
            SearchWay( next_x,next_y );
	    next_x=m_x;
        }
        else if ( next_y > m_y && Engine::Get().GetAabb()->IsOver(tmp)){
            SearchWay( next_x,next_y );
	    next_y=m_y;
        }      
  }
  if(Engine::Get().GetEntityFactory()-> CollidesWithEntity(tmp,this)){
    SearchWay( next_x,next_y );
    next_y=m_y;
     next_x=m_x;
  }
  
  m_x=next_x;
  m_y=next_y; 
}

void Entity::SearchWay(double& next_x, double& next_y ){
    
   SDL_Rect posRect={next_x,next_y,Engine::Get().GetLua()->PLAYER_SIZE,
		    Engine::Get().GetLua()->PLAYER_SIZE};   
		    
  for(int j=0; j<=3; ++j){
      roll_die();
  }
		    
	int tmp=roll_die();
	
	if(tmp==1){
	   GoRight();
	}
	else if(tmp==2){
	   GoUp();
	}
	else if(tmp==3){
	  GoLeft();
	}
	else if(tmp==4){
	  GoDown();
	}  
}


void EntityFactory::AddEntity(const ushort& X, const ushort& Y,
			      const string& Name){ 
     m_entity.push_back(*(new Entity(X,Y,Name)));

}

void EntityFactory::Update(const double& dt){
  vector<Entity>::iterator it;
  
  for(it=m_entity.begin(); it!=m_entity.end(); ++it){
      it->Update(dt);   
  }  
}

void EntityFactory::Draw(){
    vector<Entity>::iterator it;
  for(it=m_entity.begin(); it!=m_entity.end(); ++it){
      it->Draw();   
  }  
}

EntityFactory::EntityFactory(){  
  
  
}


void Entity::GoUp(){
  m_state=ES::Up;
}

void Entity::GoDown(){
  m_state=ES::Down;
}

void Entity::GoRight(){
  m_state=ES::Right;
}

void Entity::GoLeft(){
  m_state=ES::Left;
}

bool EntityFactory::CollidesWithEntity(const SDL_Rect& checkBox,Entity* Ptr){
 BOOST_FOREACH(Entity it, m_entity ) {
   if( (*Ptr) == it ) continue;
        if (   (it.m_x) > ( checkBox.x + checkBox.w )
                ||(it.m_x +  Engine::Get().GetLua()->PLAYER_SIZE) < ( checkBox.x)
                ||(it.m_y) > ( checkBox.y + checkBox.h )
                ||(it.m_y +  Engine::Get().GetLua()->PLAYER_SIZE) < ( checkBox.y )
           ) continue;
        else return true;
    }
    return false;
}


bool Entity::operator==(Entity it) const{
    if( it.GetX() == m_x 
        && it.GetY() == m_y ) return true;
    
return false; 
}



