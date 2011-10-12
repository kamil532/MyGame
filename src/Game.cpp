#include "Game.hpp"
#include "GlobFun.cpp"
#include "Engine.hpp"

Game::Game( SDL_Surface* Screen, size_t Screen_w, size_t Screen_h):
        m_screen_height(Screen_h),m_screen_width(Screen_w),m_screen(Screen),
        m_current_level(1)
{
    //Elementy graficzne pokazywane podczas ladowania aplikacji
    float m_load_progress=0;
    SDL_Surface* m_border=IMG_Load("data/pic/bar.png");
    SDL_Surface* m_filling= IMG_Load("data/pic/fill.png");

    //Pasek ladowania aplikacji
    SDL_Rect m_border_box={
        (m_screen_width-400 )/2,
        (m_screen_height * 0.85),
        400,25
    };

    SDL_Rect m_filling_box={
        ( (m_screen_width-400)/2)-2,
        (m_screen_height * 0.85) ,
        490, 25
    };

    SDL_Rect m_filling_offset={0,0,0,24};

    //Pokazanie paska przed ladowaniem wazniejszych modulow
    SDL_BlitSurface(m_filling,&m_filling_offset, m_screen, &m_filling_box);
    SDL_BlitSurface(m_border,NULL,m_screen,   &m_border_box);
    SDL_Flip(m_screen);

    //Wyslanie adresu glownego surface do engine (a potem do klas uzywajacych tego np.renderer)
    Engine::Get().SetScreen(m_screen, m_screen_width, m_screen_height);

    //Wywolanie konstruktorow klas ktore przechowuje Engine
    Engine::Get().Load();

    m_game_menu.reset( new Menu() );
    m_game_menu->Next();
    m_game_state = m_game_menu->GetGameStatePtr();
    Engine::Get().GetLeveling()->SetGameStatePtr( m_game_state );

    //Wyswietlanie paska postepu
    if (Engine::GetLua()->IMAGINATION) {

        for (; m_load_progress <= 1.0; m_load_progress+=0.01 ) {
            m_filling_offset.w= 348 * m_load_progress;
            SDL_BlitSurface(m_border,NULL,m_screen,   &m_border_box);
            SDL_BlitSurface(m_filling,&m_filling_offset, m_screen, &m_filling_box);

            SDL_Flip(m_screen);
            SDL_Delay(20);
        }
    }
//Zwolnienie surface`ow  paska i wypelnienia
    SDL_FreeSurface( m_border );
    SDL_FreeSurface( m_filling );
}

void Game::ProcessEvents() {
    //Zmienna bool wspolna z klasa App
    if ( *m_is_done ) return;

    //W zaleznosci od stanu aplikacji, inne klasy przejmuja sterowanie
    if ( *m_game_state==GS::Play ) ControlGame();
    else if ( *m_game_state==GS::MainMenu
              || *m_game_state==GS::About  ) ControlMenu();
    else if ( *m_game_state==GS::SelectLevel ) NewGame();
}

void Game::Update(const double& dt) {

    /** Jezeli stan gry to play to dokonujemy aktualizacji
    a gdy pokazane jest menu, nie aktualizujemy gry */           
 
    if(  Engine::Get().GetLeveling()->PlayerDie() ) return ;
    
    if ( (*m_game_state) == GS::Play) {
        Engine::Get().GetEntityFactory()->Update(dt);
        m_player->Update(dt);
	return;
    }
 
  
 
}

void Game::Draw() {

    SDL_FillRect( m_screen, NULL, 0x00);    
     

    if ( (*m_game_state) == GS::Play ) {
        if ( Engine::Get().GetTreasure()->WasFoundAll() ) {

            //Sytuacja kiedy znajdziemy wszystkie monety na mapie
            if (Engine::Get().GetLua()->LEVEL_MOUNT > m_current_level) {
                Engine::Get().GetGrid()->Draw();
                Engine::Get().GetLeveling()->NextLevel();

                Engine::Get().NextLevel();
                m_player.reset( new Player() );
                m_player->SetGrid( Engine::Get().GetGrid());
                Engine::Get().GetGrid()->Draw();
                ++m_current_level;
                return;
            }
        }
        Engine::Get().GetGrid()->Draw();
        m_player->Draw();
        Engine::Get().GetEntityFactory()->Draw();
        SDL_Flip(m_screen);
        SDL_Delay(1);
        return;
    }

    else if ( (*m_game_state) == GS::MainMenu ) {
        m_game_menu->Draw();
        SDL_Flip(m_screen);
        SDL_Delay(1);
        return;
    }
    else if ( (*m_game_state) == GS::About) {
        m_game_menu->Draw();
        SDL_Flip(m_screen);
        SDL_Delay(1);
        return;
    }
}

void Game::ControlGame() {

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *m_is_done = true;
            break;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            *m_game_state=GS::MainMenu;
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

void Game::ControlMenu() {

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *m_is_done = true;
            break;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            if ( (*m_game_state) == GS::MainMenu) {
                * m_is_done = true;
                break;
            }
            else if ( (*m_game_state) == GS::About )
                *m_game_state=GS::MainMenu;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
            m_game_menu->Prev();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {
            m_game_menu->Next();
        }
        else if ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN ) {
            m_game_menu->PressReturn();
        }
    }
}

void Game::NewGame() {
    m_current_level = Engine::Get().GetLeveling()->GetLevelNumber();
    (*m_game_state) = GS::Play;
    m_game_menu->SetResume();
    m_player.reset( new Player() );
    Engine::Get().GetLeveling()->StartGame();
    Engine::Get().GetLeveling()->StartNewGame();
    m_player->SetGrid( Engine::Get().GetGrid());
}