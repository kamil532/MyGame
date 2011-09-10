print("\nSprite.lua");
TILE_SIZE = 23;
PLAYER_SIZE = 42;
-- tex_x, tex_y,  pos_x,  pos_y,   width,      height,    frame_count,frame_time,loop  
cxx_add_sprite("fruit", 264 , 0 , 0 , 0 , 28 , 35 , 1 , 1 , 0 );
cxx_add_sprite("livebar", 0 ,300 , 30 , 10 , 300 , 90 , 1 , 1 , 0);
cxx_add_sprite("livebarback", 0 , 42 , 10 , 20 , 110 , 25 , 1 , 1 , 0);
cxx_add_sprite("menuItem",0, 244, 340, 275 , 60 ,55,1, 1,1); 
cxx_add_sprite("loadBar", 60, 245,300,670, 500, 50, 1, 1, 1); 
cxx_add_sprite("loadBarFill", 0, 40,312,670 , 500,50, 1, 1, 1); 
cxx_add_sprite("stand",0, 0, 30, 30,PLAYER_SIZE, PLAYER_SIZE,1, 1, 1); 
cxx_add_sprite("goLeft",168,  0, 30, 30,PLAYER_SIZE, PLAYER_SIZE,  2, 0.3, 1)
cxx_add_sprite("goRight",85,   0,  30, 	30,PLAYER_SIZE, PLAYER_SIZE, 2, 0.3, 1);  
cxx_add_sprite("goUp",	  43,   0, 30, 30,PLAYER_SIZE,PLAYER_SIZE, 1, 1,1);  
cxx_add_sprite("goDown", 43,   0, 30, 	30,PLAYER_SIZE, PLAYER_SIZE, 1, 1,1);  
cxx_add_sprite("platform_left", 0, 205,  0, 0, TILE_SIZE,  TILE_SIZE,  1, 1,0);
cxx_add_sprite("platform_mid",  0,  205,  0, 0, TILE_SIZE,  TILE_SIZE,  1, 1,0);
cxx_add_sprite("platform_right",0,  205, 0, 0, TILE_SIZE,  TILE_SIZE, 1, 1,0);




