#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "Heders.hpp"
#include "Sprite.hpp"

class Entity{ 
public:  
    void Update(const double&);
    void Draw(){ 
      m_sprite->Draw(m_x,m_y);      
    }
   inline void GoUp();
   inline void GoDown();
   inline void GoLeft();
   inline void GoRight();
  
private:  
    Entity(const ushort& X, const ushort& Y,const string& name);
    double NextXPosition(const double& dt){
	return m_x + m_vx * dt;    
    }
    double NextYPosition(const double& dt){
	 return m_y + m_vy * dt;     
    }
   void SearchWay(double&, double&);
private:    
    SpritePtr m_sprite;    
    ES::EntityState m_state;
    ushort m_x;
    ushort m_y;
    short m_vx;
    short m_vy;
   
    //tylko entity factory moze tworzy obiekty tej klasy
    friend class EntityFactory;
};


class EntityFactory{
public:	
    explicit EntityFactory();
    void AddEntity(const ushort&, const ushort&,const string& name);
    bool Colidies(const SDL_Rect&);
    void Update(const double& dt);
    void Draw();
    
private:
    vector<Entity> m_entity; 
};
typedef boost::shared_ptr<EntityFactory> EntityFactoryPtr;

#endif