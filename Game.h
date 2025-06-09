#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Player.h"
#include "WordManager.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FONT_SIZE = 40;
const int DRAGON_Y_OFFSET = 50; 

enum GameScreen { MENU = 0, GAMEPLAY, GAME_OVER };

class Game {
private:
    GameScreen currentScreen;
    Player player; 
    WordManager wordManager;

    Texture2D gameplayBackgroundTexture; 
    Texture2D menuGameOverBackgroundTexture; 
    Vector2 currentWordPosition; 

    Music backgroundMusic;
    Sound correctSound;
    Sound lifeLostSound;


    void UpdateMenu();
    void DrawMenu();

    void UpdateGameplay();
    void DrawGameplay();

    void UpdateGameOver();
    void DrawGameOver();

    void GenerateNewWordPosition();

public:
    Game(); 
    ~Game(); 

    void Run(); 
    void ResetGame(); 
};

#endif 