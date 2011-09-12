#include "SpriteConfig.hpp"
#include "Engine.hpp"

SpriteConfig::SpriteConfig(){}

bool SpriteConfig::Contains(const string& name) const{
		
	if(_data.find(name) != _data.end())  return true;  
	else cout<<"[Critical] String:"<<name.c_str(); 
	throw (" -Nieznana nazwa sprita");
	
} 

SpriteData SpriteConfig::Get(const string& name) const{	
    if (Contains(name)) return _data.find(name)->second;
	throw("[Critical] Config not found: " + name);  
}
