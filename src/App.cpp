#include "App.hpp"

void App::InitSDL() throw (const char*) {

    //![1] Inicjacja SDL-a
    if (SDL_Init( SDL_INIT_AUDIO
                  |SDL_INIT_VIDEO
                  |SDL_INIT_TIMER ) == -1) 
      throw "[Critical] Nie udalo sie zainicjowac SDL-a\n";

    SDL_ShowCursor(false);
    SDL_WM_SetCaption( STITLE.c_str() , STITLE.c_str() );

    /// Pobranie rozdzielczosci ekranu
    const SDL_VideoInfo* myPointer = SDL_GetVideoInfo();
    m_screen_h=myPointer->current_h;
    m_screen_w=myPointer->current_w;

    m_screen = SDL_SetVideoMode(m_screen_w, m_screen_h, 32, 0
                                |SDL_HWSURFACE
                                |SDL_DOUBLEBUF
                                //|SDL_FULLSCREEN
                                |SDL_ANYFORMAT    );

    if (m_screen==NULL) throw "[Critical] Nie udalo sie utworzyc powierchni glownej\n";

}

App::App(): m_screen(NULL), m_is_done(false) {

    InitSDL();
    Engine::Get().SetScreen(m_screen);
    Engine::Get().Load();

    m_level.reset(new Level());
    m_level->LoadFromFile("data/1.lvl");
  
m_grid.StoreSprite(FT::PlatformLeftEnd,  SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_left"))));
m_grid.StoreSprite(FT::PlatformMidPart,  SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_mid"))));
m_grid.StoreSprite(FT::PlatformRightEnd, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_right"))));
m_grid.StoreSprite(FT::Fruit, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("fruit"))));
m_grid.SetLevel(m_level);


m_player.reset( new Player() );
m_player->SetGrid(&m_grid);
Engine::Get().GetTreasure()->SetGrid(&m_grid);
}

void App::Run() {

    float dt (0.0f);
    float accumulator (0.0f);
    float last_ticks = SDL_GetTicks();

    /// Glowna petla programu
    while ( !m_is_done ) {

        size_t ticks = SDL_GetTicks();
        dt = (ticks - last_ticks) / 1000.0;
        last_ticks = ticks;
        accumulator += dt;

        ProcessEvents();

        while (accumulator > TIME_STEP)
        {
            Update(TIME_STEP);
            accumulator -= TIME_STEP;
        }

        Draw();
    }

    SDL_Quit();
}

void App::Update(double dt) {
  m_player->Update( dt );
}

void App::Draw() const {

    /// Zablokowanie ekranu na czas rysowania
    if ( SDL_MUSTLOCK(m_screen) ) {
        if ( SDL_LockSurface(m_screen) < 0 ) {
            return;
        }
    }

    SDL_FillRect( m_screen,NULL,0x0f);

    //rysowanie
    m_grid.Draw();
    m_player->Draw();
    Engine::Get().GetWriter()->Write();
    
    /// Odblokowanie ekranu
    if ( SDL_MUSTLOCK(m_screen) ) {
        SDL_UnlockSurface(m_screen);
    }

    SDL_Flip(m_screen);

}

void App::ProcessEvents() {

    if (m_is_done) {
        return;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_is_done = true;
            break;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            m_is_done=true;
            break;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
	  m_player->StopState();  
	  m_player->GoRight();
        }
        else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT) {	    
	  m_player->StopRight();
        }
        else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) {	   
	  m_player->StopLeft();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
	  m_player->StopState();  
	  m_player->GoLeft();
        }
        else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP) {	   
	  m_player->StopUp();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
	  m_player->StopState();   
	  m_player->GoUp();
        }
        else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {	    
	  m_player->StopDown();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {
	  m_player->StopState();    
	  m_player->GoDown();
        }
    }
}

