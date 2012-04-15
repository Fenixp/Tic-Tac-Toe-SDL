//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

void CApp::OnExit() {
    Running = false;
}

void CApp::OnLButtonDown(int mX, int mY)
{
    if(GameState == GAME_STATE_MENU)
        MenuClick(mX, mY);
    else if(GameState == GAME_STATE_VICTORY)
        VictoryClick(mX, mY);
    else
        GameClick((mX / 200) + ((mY / 200) * 3));
}

//==============================================================================
