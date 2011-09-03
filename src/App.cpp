#include "App.hpp"


void App::SetAppMode(const string* Mode){
  
  if( Mode->compare("windowMode") == 0 ){
	  m_full=0;
	  cout<<"[Info] Window mode is set\n";
    }
}

void App::InitSDL() throw (const char*) {

    //![ Inicjacja SDL-a ]
    if (SDL_Init( SDL_INIT_AUDIO
                  |SDL_INIT_VIDEO
                  |SDL_INIT_TIMER ) == -1) 
      throw "[Critical] Nie udalo sie zainicjowac SDL-a\n";

    
    if( TTF_Init() == -1 ) throw "[Critical] Inicjacja SDL_ttf";
       
    //Cala obsluga wejscia przejmuje klawiatura
    SDL_ShowCursor(false);
    
    //Ustawienie tytulu okna, oraz ikony
    SDL_WM_SetCaption( STITLE.c_str() , NULL );

    //![ Pobranie rozdzielczosci ekranu ]
    const SDL_VideoInfo* myPointer = SDL_GetVideoInfo();
    m_screen_h=myPointer->current_h;
    m_screen_w=myPointer->current_w;

    m_screen = SDL_SetVideoMode(m_screen_w, m_screen_h, 32, 0
                                |SDL_HWSURFACE
                                |SDL_DOUBLEBUF
                                |m_full
                                |SDL_ANYFORMAT    );

    if (m_screen==NULL) throw "[Critical] Nie udalo sie utworzyc powierchni glownej\n";

}

App::App(const string* Parameters): m_screen(NULL), m_is_done(false), m_full(SDL_FULLSCREEN) {

    //Parametry przekazane z maina
    SetAppMode(Parameters);
    
    //Inicjacja SDL-a
    InitSDL();
    
    //Wyslanie adresu glownego surface do engine (a potem do klas uzywajacych tego np.renderer)
    Engine::Get().SetScreen(m_screen, m_screen_w, m_screen_h);
    
    //Inicjowanie klasy Menu, ktora "przejmie" kontrole nad applikacja
    m_menu.reset( new Menu( m_screen, m_screen_w, m_screen_h) );    
    
    //Pokazanie intro do gry na poczatku
    m_menu->DrawIntro();
    
    //Wywolanie konstruktorow klas ktore przechowuje Engine
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
    size_t ticks=0;
    
    SDL_Delay(INTRO_TIME); //Czas na pokazanie intro
    
    /// Glowna petla programu
    while ( !m_is_done ) {
        ticks = SDL_GetTicks();
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

  /*  /// Zablokowanie ekranu na czas rysowania
    if ( SDL_MUSTLOCK(m_screen) ) {
        if ( SDL_LockSurface(m_screen) < 0 ) {
            return;
        }
    }*/

  //SDL_FillRect( m_screen,NULL,0x0f);
  SDL_FillRect( m_screen,NULL,SDL_MapRGB(m_screen->format,68,68,68));
    m_grid.Draw();
    m_player->Draw();
    Engine::Get().GetWriter()->Render();
    
  /*  /// Odblokowanie ekranu
    if ( SDL_MUSTLOCK(m_screen) ) {
        SDL_UnlockSurface(m_screen);
    }*/

    SDL_Flip(m_screen);
    SDL_Delay(10);

}

void App::ProcessEvents() {

    if (m_is_done) {
        return;
    }

    
   
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_is_done = true;
            break;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
	    m_menu->ShowMenu();
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
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LSHIFT) {
	  m_player->StartRun();   
        }
        else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LSHIFT) {
	  m_player->StopRun();
        }
    }
}

App::~App(){
  //Dokonczyc odsmiecanie [!!]
  
  SDL_Quit();
  TTF_Quit(); 
}