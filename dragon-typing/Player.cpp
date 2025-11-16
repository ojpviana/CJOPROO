#include "Player.h"

Player::Player(int initialLives) : maxLives(initialLives) {
    Reset();
}

void Player::LoseLife() {
    lives--;
}

void Player::AddScore(int points) {
    score += points;
}

void Player::Reset() {
    lives = maxLives;
    score = 0;
}