#ifndef SPRITECONFIG_HPP
#define SPRITECONFIG_HPP
#include "Heders.hpp"

typedef struct {
    ushort tex_x;
    ushort tex_y;
    short pos_x;
    short pos_y;
    ushort width;
    ushort height;
    ushort frame_count;
    float frame_time;
    bool loop;
}SpriteData;

class SpriteConfig{
  
public:
      SpriteConfig();
      
      SpriteData Get(const string& name) const;     
      bool Contains(const string& name) const;  
      void Insert(const string& name, ushort tex_x, ushort tex_y, short pos_x,
                  short pos_y, ushort width,ushort height, ushort frame_count,
                  float frame_time ,bool loop ){  				  	  
		 SpriteData tmp={tex_x,tex_y,pos_x,pos_y,width,height,frame_count,frame_time,loop};
		_data.insert(std::make_pair(name, tmp));
	  }
     
	  
private:
      void Insert(const string& name, SpriteData& data){
			_data.insert(std::make_pair(name, data));  
		} 
     
private:
      std::map<string , SpriteData> _data; 
};

typedef boost::shared_ptr<SpriteConfig> SpriteConfigPtr;

#endif
