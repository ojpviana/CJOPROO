

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

    currentGameState = MENU; // Começa no menu principal
    currentDifficulty = NORMAL;
    LoadHighScores(); // Carrega o placar ao iniciar o jogo

    gameplayBackgroundTexture = LoadTexture("assets/background_dragon.jpg");
    if (gameplayBackgroundTexture.id == 0) {
        TraceLog(LOG_ERROR, "GAME: Failed to load assets/background_dragon.jpg.");
    }

    menuGameOverBackgroundTexture = LoadTexture("assets/menu_background.jpg");
    if (menuGameOverBackgroundTexture.id == 0) {
        TraceLog(LOG_ERROR, "GAME: Failed to load assets/menu_background.jpg.");
    }

    backgroundMusic = LoadMusicStream("assets/medieval-background.wav");
    correctSound = LoadSound("assets/correct_sound.mp3");
    lifeLostSound = LoadSound("assets/life_lost_sound.wav");

    // ... (verificações de áudio) ...
    
    // REMOVIDO: currentScreen = MENU;
    // REMOVIDO: this->GenerateNewWordPosition(); (Será chamado no InitGameplay)
}

Game::~Game() {
    StopMusicStream(backgroundMusic); // Para a música antes de descarregar
    UnloadMusicStream(backgroundMusic);
    UnloadSound(correctSound);
    UnloadSound(lifeLostSound);

    UnloadTexture(gameplayBackgroundTexture);
    UnloadTexture(menuGameOverBackgroundTexture);

    CloseAudioDevice();
    CloseWindow();
}

void Game::Update() {
    UpdateMusicStream(backgroundMusic); // Atualiza a música em CADA frame

    switch (currentGameState) {
        case MENU: UpdateMenu(); break;
        case NAME_INPUT: UpdateNameInput(); break;
        case GAMEPLAY: UpdateGameplay(); break;
        case HIGH_SCORE:
            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER)) {
                currentGameState = MENU;
            }
            break;
        case GAME_OVER: UpdateGameOver(); break;
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK); // Fundo preto padrão

    switch (currentGameState) {
        case MENU: DrawMenu(); break;
        case NAME_INPUT: DrawNameInput(); break;
        case GAMEPLAY: DrawGameplay(); break;
        case HIGH_SCORE: DrawHighScores(); break;
        case GAME_OVER: DrawGameOver(); break;
    }

    EndDrawing();
}

// REMOVIDA: A função inteira void Game::Run() foi removida. O loop agora está no main.cpp.

// REMOVIDA: A função inteira void Game::ResetGame() foi removida. (Usamos InitGameplay).

void Game::UpdateMenu() {
    if (IsKeyPressed(KEY_F)) currentDifficulty = EASY;
    if (IsKeyPressed(KEY_N)) currentDifficulty = NORMAL;
    if (IsKeyPressed(KEY_D)) currentDifficulty = HARD;

    if (IsKeyPressed(KEY_ENTER)) {
        currentGameState = NAME_INPUT;
        
        float timeLimit = normalTimeLimit;
        if (currentDifficulty == EASY) timeLimit = easyTimeLimit;
        else if (currentDifficulty == HARD) timeLimit = hardTimeLimit;
        
        wordManager.SetInitialTime(timeLimit);

    }
    
    if (IsKeyPressed(KEY_P)) {
        currentGameState = HIGH_SCORE;
    }
}

void Game::DrawMenu() {
    // Desenha o fundo
    DrawTexturePro(menuGameOverBackgroundTexture,
                   { 0.0f, 0.0f, (float)menuGameOverBackgroundTexture.width, (float)menuGameOverBackgroundTexture.height },
                   { 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT },
                   { 0.0f, 0.0f }, 0.0f, WHITE);

    int centerX = GetScreenWidth() / 2;
    int centerY = GetScreenHeight() / 2;

    // Título do Jogo
    DrawText("DRAGON TYPING", centerX - MeasureText("DRAGON TYPING", 80) / 2, centerY - 200, 80, GOLD);
    
    // Menu de Dificuldade
    DrawText("SELECIONE A DIFICULDADE:", centerX - MeasureText("SELECIONE A DIFICULDADE:", 30) / 2, centerY - 50, 30, WHITE);

    Color easyColor = (currentDifficulty == EASY) ? LIME : DARKGRAY;
    Color normalColor = (currentDifficulty == NORMAL) ? YELLOW : DARKGRAY;
    Color hardColor = (currentDifficulty == HARD) ? RED : DARKGRAY;

    DrawText("FACIL (F)", centerX - 300, centerY, 30, easyColor);
    DrawText("NORMAL (N)", centerX - MeasureText("NORMAL (N)", 30) / 2, centerY, 30, normalColor);
    DrawText("DIFICIL (D)", centerX + 200, centerY, 30, hardColor);
    
    // Instruções
    DrawText("Pressione ENTER para Começar", centerX - MeasureText("Pressione ENTER para Começar", 20) / 2, centerY + 100, 20, RAYWHITE);
    DrawText("Pressione P para Placar", centerX - MeasureText("Pressione P para Placar", 20) / 2, centerY + 140, 20, RAYWHITE);
    
    // REMOVIDO: O segundo conjunto de DrawText (duplicado) foi removido.
}

void Game::DrawGameplay() {
    // 1. Desenha o fundo do gameplay
    DrawTexturePro(gameplayBackgroundTexture,
                   { 0.0f, 0.0f, (float)gameplayBackgroundTexture.width, (float)gameplayBackgroundTexture.height }, // SourceRec
                   { 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT }, // DestRec
                   { 0.0f, 0.0f }, // Origin
                   0.0f, // Rotation
                   WHITE); // Tint color

    // 2. Obtém as palavras
    const std::string& currentWord = wordManager.GetCurrentWord();
    const std::string& typedText = wordManager.GetTypedText();

    // 3. Desenha a palavra a ser digitada (com feedback de cor)
    int currentWordX = (int)currentWordPosition.x;
    int currentWordY = (int)currentWordPosition.y;

    for (size_t i = 0; i < currentWord.length(); i++) {
        Color charColor = LIGHTGRAY; // Cor padrão para letras não digitadas
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

    // 4. Desenha o texto que o usuário está digitando
    int typedTextX = SCREEN_WIDTH / 2 - MeasureText(typedText.c_str(), FONT_SIZE) / 2;
    int typedTextY = SCREEN_HEIGHT - 100; // Posição fixa no fundo
    DrawText(typedText.c_str(), typedTextX, typedTextY, FONT_SIZE, GRAY);

    // 5. Desenha o HUD (Tempo, Vidas, Pontuação) - DEVE SER O ÚLTIMO
    DrawText(TextFormat("Tempo: %.1f", wordManager.GetWordTimer()), 20, 20, 30, DARKBLUE);
    DrawText(TextFormat("Vidas: %d", player.GetLives()), SCREEN_WIDTH - MeasureText("Vidas: X", 30) - 20, 20, 30, RED);
    DrawText(TextFormat("Pontuacao: %d", player.GetScore()), 20, 60, 30, GREEN);
}
void Game::UpdateGameplay() {
    wordManager.Update(GetFrameTime());

    if (wordManager.IsTimeUp()) {
        player.LoseLife();
        PlaySound(lifeLostSound);
        if (player.IsGameOver()) {
            // REMOVIDO: currentScreen = GAME_OVER;
            AddNewHighScore(userName, player.GetScore()); // Salva o placar
            currentGameState = GAME_OVER; // Muda para o estado de Game Over
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
        wordManager.Reset();
        this->GenerateNewWordPosition();
    }
    
    // REMOVIDO: A checagem if (player.GetLives() <= 0) foi movida para
    // a lógica de IsTimeUp(), onde faz mais sentido.
}

// ... (DrawGameplay parece correto) ...

void Game::UpdateGameOver() {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) {
        currentGameState = MENU;
    }
}

void Game::DrawGameOver() {
    // ADICIONADO: Desenha o fundo
    DrawTexturePro(menuGameOverBackgroundTexture,
                   { 0.0f, 0.0f, (float)menuGameOverBackgroundTexture.width, (float)menuGameOverBackgroundTexture.height },
                   { 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT },
                   { 0.0f, 0.0f }, 0.0f, WHITE);

    int centerX = GetScreenWidth() / 2;
    int score = player.GetScore();
    
    DrawText("FIM DE JOGO!", centerX - MeasureText("FIM DE JOGO!", 60) / 2, 100, 60, RED);
    DrawText(TextFormat("Sua Pontuação: %d", score), centerX - MeasureText(TextFormat("Sua Pontuação: %d", score), 40) / 2, 200, 40, GOLD);
    DrawText(TextFormat("Usuário: %s", userName), centerX - MeasureText(TextFormat("Usuário: %s", userName), 30) / 2, 260, 30, WHITE);
    
    DrawText("Pressione ENTER para o Menu", centerX - MeasureText("Pressione ENTER para o Menu", 20) / 2, GetScreenHeight() - 50, 20, RAYWHITE);
}

void Game::InitGameplay() {
    player.Reset();
    wordManager.Reset();
    this->GenerateNewWordPosition(); // Gera a primeira palavra
}

// ADICIONE ISTO AO SEU Game.cpp

void Game::LoadHighScores() {
    highScores.clear();
    char* fileText = LoadFileText(highScoresFileName);

    if (fileText) {
        char nameBuffer[32];
        int score;
        char* line = strtok(fileText, "\n");
        while (line != NULL) {
            if (sscanf(line, "%31[^,],%d", nameBuffer, &score) == 2) {
                HighScoreEntry entry;
                TextCopy(entry.name, nameBuffer);
                entry.score = score;
                highScores.push_back(entry);
            }
            line = strtok(NULL, "\n");
        }
        UnloadFileText(fileText);
        
        std::sort(highScores.begin(), highScores.end(), [](const HighScoreEntry& a, const HighScoreEntry& b) {
            return a.score > b.score;
        });
    }
}

void Game::SaveHighScores() {
    std::string content = "";
    for (const auto& entry : highScores) {
        content += TextFormat("%s,%d\n", entry.name, entry.score);
    }
    SaveFileText(highScoresFileName, (char*)content.c_str());
}

void Game::AddNewHighScore(const char* name, int score) {
    HighScoreEntry newEntry;
    TextCopy(newEntry.name, name);
    newEntry.score = score;
    highScores.push_back(newEntry);

    std::sort(highScores.begin(), highScores.end(), [](const HighScoreEntry& a, const HighScoreEntry& b) {
        return a.score > b.score;
    });

    if (highScores.size() > 10) {
        highScores.resize(10);
    }

    SaveHighScores();
}

void Game::DrawHighScores() {
    // Desenha o fundo
    DrawTexturePro(menuGameOverBackgroundTexture,
                   { 0.0f, 0.0f, (float)menuGameOverBackgroundTexture.width, (float)menuGameOverBackgroundTexture.height },
                   { 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT },
                   { 0.0f, 0.0f }, 0.0f, WHITE);

    int centerX = GetScreenWidth() / 2;
    int yOffset = 100;

    DrawText("PLACAR DE LÍDERES", centerX - MeasureText("PLACAR DE LÍDERES", 40) / 2, 50, 40, GOLD);

    for (size_t i = 0; i < highScores.size(); ++i) {
        const HighScoreEntry& entry = highScores[i];
        int yPos = yOffset + (int)i * 40;
        
        DrawText(TextFormat("%d.", (int)i + 1), centerX - 250, yPos, 25, RAYWHITE);
        DrawText(entry.name, centerX - 200, yPos, 25, RAYWHITE);
        DrawText(TextFormat("%d", entry.score), centerX + 150, yPos, 25, RAYWHITE);
    }
    DrawText("Pressione ESC ou ENTER para Voltar", centerX - MeasureText("Pressione ESC ou ENTER para Voltar", 20) / 2, GetScreenHeight() - 50, 20, RAYWHITE);
}

void Game::UpdateNameInput() {
    int key = GetCharPressed();
    int letterCount = TextLength(userName);

    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (letterCount < 31)) {
            userName[letterCount] = (char)key;
            letterCount++;
            userName[letterCount] = '\0';
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (letterCount > 0) {
            letterCount--;
            userName[letterCount] = '\0';
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (TextLength(userName) > 0) {
            currentGameState = GAMEPLAY;
            InitGameplay();
        }
    }
}

void Game::DrawNameInput() {
    // Desenha o fundo
    DrawTexturePro(menuGameOverBackgroundTexture,
                   { 0.0f, 0.0f, (float)menuGameOverBackgroundTexture.width, (float)menuGameOverBackgroundTexture.height },
                   { 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT },
                   { 0.0f, 0.0f }, 0.0f, WHITE);

    int centerX = GetScreenWidth() / 2;
    int centerY = GetScreenHeight() / 2;
    Rectangle textBox = { (float)centerX - 200, (float)centerY - 20, 400, 40 };

    DrawText("DIGITE SEU NOME DE USUÁRIO", centerX - MeasureText("DIGITE SEU NOME DE USUÁRIO", 30) / 2, centerY - 100, 30, GOLD);

    DrawRectangleRec(textBox, LIGHTGRAY);
    DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, MAROON);

    DrawText(userName, (int)textBox.x + 10, (int)textBox.y + 10, 20, BLACK);
    
    if (((GetTime() / 0.5f) - (int)(GetTime() / 0.5f)) < 0.5f) {
        DrawText("_", (int)textBox.x + 10 + MeasureText(userName, 20), (int)textBox.y + 10, 20, BLACK);
    }

    DrawText("Pressione ENTER para Começar", centerX - MeasureText("Pressione ENTER para Começar", 20) / 2, centerY + 100, 20, RAYWHITE);
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

    if (minY >= maxY) { minY = SCREEN_HEIGHT / 4; maxY = SCREEN_HEIGHT / 2; }
    if (minX >= maxX) { minX = SCREEN_WIDTH / 4; maxX = SCREEN_WIDTH / 2; }

    std::uniform_int_distribution<int> distX(minX, maxX);
    std::uniform_int_distribution<int> distY(minY, maxY);

    currentWordPosition.x = (float)distX(rng);
    currentWordPosition.y = (float)distY(rng);
    TraceLog(LOG_INFO, TextFormat("New word position: (%.0f, %.0f) for word: %s", currentWordPosition.x, currentWordPosition.y, currentWord.c_str()));
}