//==============================================================================
#include "CApp.h"

//==============================================================================
CApp::CApp() {
    Surf_Grid = NULL;
    Surf_O = NULL;
    Surf_X = NULL;

    Surf_Display = NULL;

    srand(time(NULL));

    CurrentPlayer = 0;

    GameState = GAME_STATE_MENU;

    Running = true;

    AIenabled = false;
}

//------------------------------------------------------------------------------
int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        if(AIenabled && CurrentPlayer && GameState == GAME_STATE_RUNNING)
        {
            GameClick(AIMove());
        }

        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

void CApp::Reset()
{
    for(int i=0; i<9; i++)
    {
        Grid[i] = GRID_TYPE_NONE;
    }
}

void CApp::SetCell(int ID, int Type)
{
    if(ID<0 || ID>=9) return;
    if(Type<0 || Type>GRID_TYPE_O) return;

    Grid[ID] = Type;
}

// Checks cell with cell- coordinates against move- coordinates;
int CApp::MoveCell(int cellX, int cellY, int moveX, int moveY)
{
    // Checks if the cell isn't checking against itself (+0; +0 move)
    if(moveX == 0 && moveY == 0)return GRID_TYPE_NONE;
    // Checks if the cell's coordinates are within the grid
    else if((cellX + moveX) < 0 || (cellX + moveX) > 2 ||
            (cellY + moveY) < 0 || (cellY + moveY) > 2)return GRID_TYPE_NONE;
    else return CheckCell((cellX + moveX) * 3 + (cellY + moveY));
}

// Returns owner of the cell
int CApp::CheckCell(int ID)
{
    if(ID < 9 && ID > -1)
    {
        return Grid[ID];
    }
    else return GRID_TYPE_NONE;
}

// Handles moves of the AI
int CApp::AIMove()
{
    int Player;
    int Move;
    int IDx;
    int IDy;

    // Checks all cells if the're empty and in line with another 2 cells of any player.
    // If it detects 2 cells in row, AI places circle that either blocks opponent or wins the game.
    for(int i = 0; i < 9; i++)
    {
        IDx = i / 3;
        IDy = i % 3;

        for(int x = -1; x < 2; x++)
            for(int y = -1; y < 2; y++)
                if((Player = MoveCell(IDx, IDy, x, y)) != GRID_TYPE_NONE && Grid[i] == GRID_TYPE_NONE)
                {
                    if(MoveCell(IDx, IDy, -x, -y) == Player)
                        return i;
                    if(MoveCell(IDx + x, IDy + y, x, y) == Player)
                        return i;
                }
    }

    // If there are no cells in a row, AI places circle at random location
    while(true)
    {
        Move = rand() % 10;
        if(Grid[Move] == GRID_TYPE_NONE)
            return Move;
    }
}

// Handles left click in main menu
void CApp::MenuClick(int mX, int mY)
{
    if(mY > 157 && mY < 213 && mX > 204 && mX < 398)
    {
        AIenabled = true;
        GameState = GAME_STATE_RUNNING;
    }
    if(mY > 273 && mY < 329 && mX > 204 && mX < 398)
    {
        AIenabled = false;
        GameState = GAME_STATE_RUNNING;
    }
    if(mY > 410 && mY < 466 && mX > 204 && mX < 398)
        OnExit();
}

// Handles left click on endgame screen
void CApp::VictoryClick(int mX, int mY)
{
    if(mY > 406 && mY < 459 && mX > 210 && mX < 404)
    {
        GameState = GAME_STATE_RUNNING;
        CurrentPlayer = 0;
        OnRestart();
    }

    if(mY > 492 && mY < 548 && mX > 210 && mX < 404)
    {
        GameState = GAME_STATE_MENU;
        CurrentPlayer = 0;
        OnRestart();
    }
}

// Handles left click during the game
void CApp::GameClick(int ID)
{
    bool full = true;

    short IDx = ID / 3;
    short IDy = ID % 3;


    if(Grid[ID] != GRID_TYPE_NONE)
        return;

    // When player clicks a cell, this cycle checks all neighbouring cells.
    // If it detects a cell of the same player, it looks for another cell in the row.
    for(int x = -1; x < 2; x++)
        for(int y = -1; y < 2; y++)
            if(MoveCell(IDx, IDy, x, y) == CurrentPlayer + 1)
            {
                if(MoveCell(IDx, IDy, -x, -y) == CurrentPlayer + 1)
                    GameState = GAME_STATE_VICTORY;
                if(MoveCell(IDx + x, IDy + y, x, y) == CurrentPlayer + 1)
                    GameState = GAME_STATE_VICTORY;
            }

    if(CurrentPlayer == 0)
    {
        SetCell(ID, GRID_TYPE_X);
        CurrentPlayer = 1;
    }else
    {
        SetCell(ID, GRID_TYPE_O);
        CurrentPlayer = 0;
    }

    for(int i = 0; i < 9; i++)
    {
        if(Grid[i] == GRID_TYPE_NONE)full = false;
    }

    // Checks if game field isn't full
    if(full)
    {
        CurrentPlayer = 2;
        GameState = GAME_STATE_VICTORY;
    }
}

//==============================================================================
int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();
}

//==============================================================================
