#include "App.hpp"

void App::SetAppMode(const string* Mode){
  
  // Argument podany mainowi podczas uruchamiania
  // Moze wlaczyc opcje przydatne przy debugowaniu  
  if( Mode->compare("windowMode") == 0 ){
	  m_full=0;
	  cout<<"[Info] Window mode is set\n";
    }
}

void App::InitSDL() throw (const char*) {

    //![ Inicjacja SDL-a ]
    if (SDL_Init(  SDL_INIT_AUDIO
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

    if (m_screen==NULL) throw "[Critical] Nie udalo sie utworzyc powierzchni glownej\n";

}

App::App(const string* Parameters): 
m_is_done( new bool(false) ), m_screen(NULL), m_full(SDL_FULLSCREEN){

    //Parametry przekazane z maina
    SetAppMode(Parameters);
    
    //Inicjacja SDL-a
    InitSDL();
    
    //Inicjowanie klasy Menu, ktora "przejmie" kontrole nad applikacja
    m_game.reset( new Game( m_screen, m_screen_w, m_screen_h) );    
    
    //Klasa Menu ma dostep do zmiennej, ktora decyduje o tym czy zakonczyc applikacje
    m_game->SetQuitFlag( m_is_done );   
}

void App::Run() {

    float dt (0.0f);
    float accumulator (0.0f);
    float last_ticks = SDL_GetTicks();
    size_t ticks=0;
    
    SDL_Delay(INTRO_TIME); //Czas na pokazanie intro
    
    //! [ Glowna petla programu ]    
    while ( !(*m_is_done) ){
        ticks = SDL_GetTicks();
        dt = (ticks - last_ticks) / 1000.0;
        last_ticks = ticks;
        accumulator += dt;
    
        m_game-> ProcessEvents();

        while (accumulator > TIME_STEP){
          m_game-> Update(TIME_STEP);
            accumulator -= TIME_STEP;
	}
        m_game->Draw();
    }
}

App::~App(){
  //Dokonczyc odsmiecanie [!!]  
  SDL_Quit();
  TTF_Quit(); 
}