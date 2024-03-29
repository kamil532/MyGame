#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "Heders.hpp"
#include "Sprite.hpp"

class Renderer {
public:

    Renderer(SDL_Surface* Screen, const string& filename);

    void Draw( size_t tex_x, size_t tex_y,
               size_t pos_x, size_t pos_y,
               size_t width, size_t height );
    void Draw( const SpritePtr _Sprite );
    void Draw( const Sprite* _Sprite, uint frame);
    void Draw( SDL_Surface* _Surface ,SDL_Rect dest);
    void Draw( SDL_Surface* _Surface );

private:
    SDL_Surface* m_screen; // 
    SDL_Surface* m_atlas;  //
  
};
typedef boost::shared_ptr<Renderer> RendererPtr;

#endif
