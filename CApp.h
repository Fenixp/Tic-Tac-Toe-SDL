//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include "CSurface.h"
#include "CEvent.h"

//==============================================================================
class CApp : public CEvent {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;

    private:
        SDL_Surface*    Surf_Grid;

        SDL_Surface*    Surf_X;
        SDL_Surface*    Surf_O;

        SDL_Surface*    Surf_Victory;

        SDL_Surface*    Surf_Menu;

        SDL_Surface*    Surf_Draw;

    private:
        int             Grid[9];

        int             CurrentPlayer;

        enum {
            GRID_TYPE_NONE = 0,
            GRID_TYPE_X,
            GRID_TYPE_O
        };
        // Stores current game state
        int             GameState;
        // Possible game states
        enum
        {
            GAME_STATE_RUNNING = 0,
            GAME_STATE_VICTORY,
            GAME_STATE_MENU
        };

        // Stores whether game is single or multiplayer
        bool AIenabled;

    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

            void OnExit();

            void OnLButtonDown(int mX, int mY);

        void OnLoop();

        void OnRender();
        // Restarts the game
        void OnRestart();

        void OnCleanup();

    public:
        void Reset();

        void SetCell(int ID, int Type);

        // Checks cell with cell- coordinates against move- coordinates;
        int MoveCell(int cellX, int cellY, int moveX, int moveY);

        // Returns owner of the cell
        int CheckCell(int ID);

        // Handles moves of the AI
        int AIMove();

        // 3 functions below jandle left-click events for different game states
        void MenuClick(int mX, int mY);

        void VictoryClick(int mX, int mY);

        void GameClick(int ID);
};

//==============================================================================

#endif
