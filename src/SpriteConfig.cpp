#include "SpriteConfig.hpp"

SpriteConfig::SpriteConfig(){

  /// tex_x,tex_y,pos_x,pos_y,width,height,frame_count,frame_time,loop  
  Insert("stand", 0, 0, 30, 30, PLAYER_SIZE, PLAYER_SIZE, 2, 1, true); 
  Insert("goLeft", 44, 0, 30, 30, PLAYER_SIZE, PLAYER_SIZE, 2, 1, true);  
  Insert("goRight", 15, 0, 30, 30, PLAYER_SIZE, PLAYER_SIZE, 2, 1, true);  
  Insert("goUp", 122, 0, 30, 30, PLAYER_SIZE, PLAYER_SIZE, 2, 1, true);  
  Insert("goDown", 0, 15, 30, 30, PLAYER_SIZE, PLAYER_SIZE, 2, 1, true);  
  Insert("platform_left", 0, 220, 0, 0, TILE_SIZE, TILE_SIZE, 1, 1, false);
  Insert("platform_mid", 0, 220, 0, 0, TILE_SIZE, TILE_SIZE, 1, 1, false);
  Insert("platform_right", 0, 220, 0, 0, TILE_SIZE, TILE_SIZE, 1, 1, false);
  Insert("fruit", 400-(TILE_SIZE*2), 0, 0, 0, TILE_SIZE*2, TILE_SIZE*2, 1, 1, false);
  Insert("livebar", 0, 78, 20 , 20 , 130, 45, 1, 1, false);
  Insert("livebarback", 0, 350, 10 , 20 , 110, 25, 1, 1, false);
  
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