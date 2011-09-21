#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "Heders.hpp"
#include "Sprite.hpp"

class Entity{ 
public:  
    void Update(const double&);
   inline void GoUp();
   inline void GoDown();
   inline void GoLeft();
   inline void GoRight();
   void Draw();
   
   bool operator==(Entity) const;

   ushort GetX()const { return m_x; }
   ushort GetY()const { return m_y; }
   
   
private:  
    Entity(const ushort& X, const ushort& Y );
    double NextXPosition(const double& dt){
	return m_x + m_vx * dt;    
    }
    double NextYPosition(const double& dt){
	 return m_y + m_vy * dt;     
    }
   void SearchWay(double&, double&);
private:    
    SpritePtr m_sprite; 
    SpritePtr m_left;
    SpritePtr m_right;
    
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
    bool CollidesWithEntity(const SDL_Rect&,Entity*);
    
private:
    vector<Entity> m_entity; 
};
typedef boost::shared_ptr<EntityFactory> EntityFactoryPtr;

#endif