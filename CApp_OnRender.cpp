//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnRender() {
    CSurface::OnDraw(Surf_Display, Surf_Grid, 0, 0);

    if(GameState == GAME_STATE_MENU)
    {
        CSurface::OnDraw(Surf_Display, Surf_Menu, 0, 0);
    }

    for(int i = 0; i < 9; i++)
    {
        int X = (i % 3) * 200;
        int Y = (i / 3) * 200;

        if(Grid[i] == GRID_TYPE_X)
        {
            CSurface::OnDraw(Surf_Display, Surf_X, X, Y);
        }
        else
        if(Grid[i] == GRID_TYPE_O)
        {
            CSurface::OnDraw(Surf_Display, Surf_O, X, Y);
        }
    }

    if(GameState == GAME_STATE_VICTORY && CurrentPlayer < 2)
    {
        CSurface::OnDraw(Surf_Display, Surf_Victory, 100, 200);
        if(CurrentPlayer == 0)CSurface::OnDraw(Surf_Display, Surf_O, 80, 200);
        if(CurrentPlayer == 1)CSurface::OnDraw(Surf_Display, Surf_X, 80, 200);
    }

    if(GameState == GAME_STATE_VICTORY && CurrentPlayer == 2)
    {
        CSurface::OnDraw(Surf_Display, Surf_Victory, 100, 200);
        CSurface::OnDraw(Surf_Display, Surf_Draw, 120, 210);
    }

    SDL_Flip(Surf_Display);
}

void CApp::OnRestart()
{
    CSurface::OnDraw(Surf_Display, Surf_Grid, 0, 0);
    for(int i = 0; i < 9; i++)
    {
        Grid[i] = GRID_TYPE_NONE;
    }
}

//==============================================================================
