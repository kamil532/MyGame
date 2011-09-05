#include "SpriteConfig.hpp"

SpriteConfig::SpriteConfig(){

  ///			 tex_x, tex_y,  pos_x,  pos_y,   width,      height,    frame_count,frame_time,loop  
  Insert("stand",         0, 	0,	 30, 	30,	PLAYER_SIZE, PLAYER_SIZE,    1, 1, 	true); 
  Insert("goLeft",	  168,  0, 	 30, 	30,	PLAYER_SIZE, PLAYER_SIZE,    2, 0.3,	true);  
  Insert("goRight",	  85,   0, 	 30, 	30, 	PLAYER_SIZE, PLAYER_SIZE,    2, 0.3,	true);  
  Insert("goUp",	  43,   0, 	 30, 	30, 	PLAYER_SIZE, PLAYER_SIZE,    1, 1, 	true);  
  Insert("goDown",	  43,   0, 	 30, 	30, 	PLAYER_SIZE, PLAYER_SIZE,    1, 1,	true);  
  Insert("platform_left", 0,    205, 	 0, 	0, 	TILE_SIZE,   TILE_SIZE,      1, 1,	false);
  Insert("platform_mid",  0,    205, 	 0, 	0, 	TILE_SIZE,   TILE_SIZE,      1, 1, 	false);
  Insert("platform_right",0,    205,	 0, 	0, 	TILE_SIZE,   TILE_SIZE,      1, 1, 	false);
  Insert("fruit", 	  60 , 150, 	 0, 	0, 	28,	     35, 	     1, 1, 	false);
  Insert("livebar",       305,  0, 	 20 ,   20 , 	130,         45, 	     1, 1, 	false);
  Insert("livebarback",   0,    42,      10 ,   20 , 	110,         25, 	     1, 1, 	false);
  Insert("menuItem",      0,    240, 	 470,   290, 	60,         100, 	     1, 1, 	true); 
  Insert("loadBar",       60,   245, 	 300,   670,	500,         50, 	     1, 1, 	true); 
  Insert("loadBarFill",   0,    40, 	 312,   670,	500,         50, 	     1, 1, 	true); 
}

bool SpriteConfig::Contains(const string& name) const{
		
	if(_data.find(name) != _data.end())  return true;  
	else cout<<"[Critical] String:"<<name.c_str(); 
	throw (" -Nieznana nazwa sprita");
	
} 

SpriteData SpriteConfig::Get(const string& name) const{	
    if (Contains(name)) return _data.find(name)->second;
	throw("[Critical] Config not found: " + name);  
}
