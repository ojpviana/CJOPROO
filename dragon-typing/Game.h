// Game.h (Versão Limpa e Corrigida)

#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Player.h"
#include "WordManager.h"

#include <vector>
#include <algorithm>
#include <cstring>

// --- Constantes Globais ---
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FONT_SIZE = 40; 

// --- Enums de Estado e Dificuldade ---
enum GameState {
    MENU,
    NAME_INPUT,
    GAMEPLAY,
    HIGH_SCORE,
    GAME_OVER
};

enum Difficulty {
    EASY,
    NORMAL,
    HARD
};

// --- Estrutura do Placar ---
struct HighScoreEntry {
    char name[32];
    int score;
};

// (O enum GameScreen foi REMOVIDO)

class Game {
private:
    // (A variável currentScreen foi REMOVIDA)
    Player player;
    WordManager wordManager;
    GameState currentGameState; // O único controlador de estado
    Difficulty currentDifficulty;

    Texture2D gameplayBackgroundTexture;
    Texture2D menuGameOverBackgroundTexture;
    Vector2 currentWordPosition;

    Music backgroundMusic;
    Sound correctSound;
    Sound lifeLostSound;

    // Constantes de Dificuldade
    const float easyTimeLimit = 5.0f;
    const float normalTimeLimit = 3.0f;
    const float hardTimeLimit = 1.5f;

    // Variáveis do Placar
    char userName[32] = "\0";
    std::vector<HighScoreEntry> highScores;
    const char* highScoresFileName = "leaderboard.txt";

    // --- Métodos Privados (Handlers de Estado) ---
    void InitGameplay();
    void UpdateMenu();
    void DrawMenu();
    void UpdateNameInput();
    void DrawNameInput();
    void UpdateGameplay();
    void DrawGameplay();
    void UpdateGameOver();
    void DrawGameOver();
    void GenerateNewWordPosition();

    // Métodos do Placar
    void LoadHighScores();
    void SaveHighScores();
    void AddNewHighScore(const char* name, int score);
    void DrawHighScores();

public:
    Game();
    ~Game();

    // Funções principais chamadas pelo main.cpp
    void Update();
    void Draw();

    // (As funções Run() e ResetGame() foram REMOVIDAS)
};

#endif