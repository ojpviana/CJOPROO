#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h" 

const int MAX_LIVES = 3; 

class Player {
private:
    int lives;
    int score;
    int maxLives;

public:
    Player(int initialLives = 3);
    void LoseLife();
    void AddScore(int points);
    void Reset();

    int GetLives() const { return lives; }
    int GetScore() const { return score; }
    bool IsGameOver() const { return lives <= 0; }
};

#endif 