#include "Game.h"
#include <string>
#include <random> 
#include <algorithm> 

std::random_device rd;
std::mt19937 rng(rd());

Game::Game() : player(MAX_LIVES), wordManager(WORD_TIME_LIMIT) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dragon Typing");
    SetTargetFPS(60);
    InitAudioDevice();

    gameplayBackgroundTexture = LoadTexture("assets/background_dragon.jpg"); 
    if (gameplayBackgroundTexture.id == 0) {
        TraceLog(LOG_ERROR, "GAME: Failed to load assets/background_dragon.jpg. Check file path.");
    }

    menuGameOverBackgroundTexture = LoadTexture("assets/menu_background.jpg"); 
    if (menuGameOverBackgroundTexture.id == 0) {
        TraceLog(LOG_ERROR, "GAME: Failed to load assets/menu_background.jpg. Check file path.");
    }

    backgroundMusic = LoadMusicStream("assets/medieval-background.wav");
    correctSound = LoadSound("assets/correct_sound.mp3");
    lifeLostSound = LoadSound("assets/life_lost_sound.wav");

    if (backgroundMusic.frameCount == 0) TraceLog(LOG_ERROR, "Failed to load medieval-background.wav");
    if (correctSound.frameCount == 0) TraceLog(LOG_ERROR, "Failed to load correct_sound.mp3");
    if (lifeLostSound.frameCount == 0) TraceLog(LOG_ERROR, "Failed to load life_lost_sound.wav");

    currentScreen = MENU;
    this->GenerateNewWordPosition();
}

Game::~Game() {
    UnloadMusicStream(backgroundMusic);
    UnloadSound(correctSound);
    UnloadSound(lifeLostSound);

    UnloadTexture(gameplayBackgroundTexture); 
    UnloadTexture(menuGameOverBackgroundTexture); 

    CloseAudioDevice();
    CloseWindow();
}

void Game::Run() {
    PlayMusicStream(backgroundMusic);

    while (!WindowShouldClose()) {
        UpdateMusicStream(backgroundMusic);

        switch (currentScreen) {
            case MENU:     UpdateMenu();     break;
            case GAMEPLAY: UpdateGameplay(); break;
            case GAME_OVER:UpdateGameOver(); break;
            default: break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE); 

        switch (currentScreen) {
            case MENU:     DrawMenu();     break;
            case GAMEPLAY: DrawGameplay(); break;
            case GAME_OVER:DrawGameOver(); break;
            default: break;
        }
        EndDrawing();
    }
    StopMusicStream(backgroundMusic);
}

void Game::ResetGame() {
    player.Reset();
    wordManager.Reset();
    currentScreen = MENU; 
}

void Game::UpdateMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = GAMEPLAY;
        player.Reset(); 
        wordManager.Reset(); 
        this->GenerateNewWordPosition(); 
    }
}

void Game::DrawMenu() {

    DrawTexturePro(menuGameOverBackgroundTexture,
                   { 0.0f, 0.0f, (float)menuGameOverBackgroundTexture.width, (float)menuGameOverBackgroundTexture.height }, // SourceRec
                   { 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT }, 
                   { 0.0f, 0.0f }, 
                   0.0f, 
                   WHITE); 

    int titleFontSize = 90;
    int titleX = SCREEN_WIDTH / 2 - MeasureText("DRAGON TYPING", titleFontSize) / 2;
    int titleY = SCREEN_HEIGHT / 4 - 100; 
    Color titleColor = GOLD;
    DrawText("DRAGON TYPING", titleX, titleY, titleFontSize, titleColor);

    int enterFontSize = 40;
    int enterTextWidth = MeasureText("Pressione ENTER para Comecar", enterFontSize);
    int enterTextX = SCREEN_WIDTH / 2 - enterTextWidth / 2;
    int enterTextY = SCREEN_HEIGHT / 2 + 150; 
    Color enterTextColor = LIGHTGRAY;
    DrawText("Pressione ENTER para Comecar", enterTextX, enterTextY, enterFontSize, enterTextColor);


    int infoFontSize = 25;
    int infoTextWidth = MeasureText("Digite as palavras antes que o tempo acabe!", infoFontSize);
    int infoTextX = SCREEN_WIDTH / 2 - infoTextWidth / 2;
    int infoTextY = enterTextY + 60; 
    Color infoTextColor = GRAY;
    DrawText("Digite as palavras antes que o tempo acabe!", infoTextX, infoTextY, infoFontSize, infoTextColor);
}


void Game::UpdateGameplay() {

    wordManager.Update(GetFrameTime());

    if (wordManager.IsTimeUp()) {
        player.LoseLife();
        PlaySound(lifeLostSound);
        TraceLog(LOG_INFO, TextFormat("Tempo esgotado! Vidas restantes: %d", player.GetLives()));
        if (player.IsGameOver()) {
            currentScreen = GAME_OVER;
        } else {
            wordManager.Reset(); 
            this->GenerateNewWordPosition();
        }
    }

    int key = GetCharPressed();
    wordManager.HandleInput(key);

    if (IsKeyPressed(KEY_BACKSPACE)) {
        wordManager.HandleBackspace();
    }

    if (wordManager.IsWordCorrect()) {
        player.AddScore(10); 
        PlaySound(correctSound);
        TraceLog(LOG_INFO, TextFormat("Palavra correta! Pontuação: %d", player.GetScore()));
        wordManager.Reset();
        this->GenerateNewWordPosition();
    }
}

void Game::DrawGameplay() {

    DrawTexturePro(gameplayBackgroundTexture,
    { 0.0f, 0.0f, (float)gameplayBackgroundTexture.width, (float)gameplayBackgroundTexture.height }, // SourceRec
    { 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT }, 
    { 0.0f, 0.0f }, 
    0.0f, 
    WHITE); 

    const std::string& currentWord = wordManager.GetCurrentWord();
    const std::string& typedText = wordManager.GetTypedText();

    int currentWordX = (int)currentWordPosition.x;
    int currentWordY = (int)currentWordPosition.y;

        for (size_t i = 0; i < currentWord.length(); i++) {
            Color charColor = LIGHTGRAY;
            if (i < typedText.length()) { 
                if (currentWord[i] == typedText[i]) {
                    charColor = GREEN;
                } else {
                    charColor = RED;
                }
            }
            int charX = currentWordX + MeasureText(currentWord.substr(0, i).c_str(), FONT_SIZE);
            DrawText(TextFormat("%c", currentWord[i]), charX, currentWordY, FONT_SIZE, charColor);
    }

            int typedTextX = SCREEN_WIDTH / 2 - MeasureText(typedText.c_str(), FONT_SIZE) / 2;
            int typedTextY = SCREEN_HEIGHT - 100;
            DrawText(typedText.c_str(), typedTextX, typedTextY, FONT_SIZE, GRAY);


    DrawText(TextFormat("Tempo: %.1f", wordManager.GetWordTimer()), 20, 20, 30, DARKBLUE);


    DrawText(TextFormat("Vidas: %d", player.GetLives()), SCREEN_WIDTH - MeasureText("Vidas: X", 30) - 20, 20, 30, RED);


    DrawText(TextFormat("Pontuacao: %d", player.GetScore()), 20, 60, 30, GREEN);
}

void Game::UpdateGameOver() {
    if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = MENU; 
    }
}

void Game::DrawGameOver() {


    DrawTexturePro(menuGameOverBackgroundTexture,
    { 0.0f, 0.0f, (float)menuGameOverBackgroundTexture.width, (float)menuGameOverBackgroundTexture.height }, // SourceRec
    { 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT }, 
    { 0.0f, 0.0f }, 
    0.0f, 
    WHITE); 

    DrawText("GAME OVER!", SCREEN_WIDTH / 2 - MeasureText("GAME OVER!", 80) / 2, SCREEN_HEIGHT / 4, 80, RED);
    DrawText(TextFormat("Pontuacao final: %d", player.GetScore()), SCREEN_WIDTH / 2 - MeasureText(TextFormat("Pontuacao final: %d", player.GetScore()), 40) / 2, SCREEN_HEIGHT / 2, 40, WHITE);
    DrawText("Pressione ENTER para Voltar ao Menu", SCREEN_WIDTH / 2 - MeasureText("Pressione ENTER para Voltar ao Menu", 30) / 2, SCREEN_HEIGHT / 2 + 100, 30, LIGHTGRAY);
}

void Game::GenerateNewWordPosition() {
    const std::string& currentWord = wordManager.GetCurrentWord();
    int wordWidth = MeasureText(currentWord.c_str(), FONT_SIZE);

    int hudTopPadding = 50; 
    int hudHeight = 50; 

    int minY = hudTopPadding + hudHeight + 50;

    int maxY = SCREEN_HEIGHT - 200; 

    int minX = 50; 
    int maxX = SCREEN_WIDTH - wordWidth - 50; 

    if (minY >= maxY) minY = SCREEN_HEIGHT / 4;
    if (minY >= maxY) maxY = SCREEN_HEIGHT / 2; 

    if (minX >= maxX) {
        minX = SCREEN_WIDTH / 4;
        maxX = SCREEN_WIDTH / 2;
    }

    std::uniform_int_distribution<int> distX(minX, maxX);
    std::uniform_int_distribution<int> distY(minY, maxY);

    currentWordPosition.x = (float)distX(rng);
    currentWordPosition.y = (float)distY(rng);

    TraceLog(LOG_INFO, TextFormat("New word position: (%.0f, %.0f) for word: %s", currentWordPosition.x, currentWordPosition.y, currentWord.c_str()));
}