#include "Game.h"

int main() {
    Game game;

    while (!WindowShouldClose()) {
        game.Update(); // Atualiza a lógica do jogo (baseado no estado)
        game.Draw();   // Desenha o jogo (baseado no estado)
    }
    return 0;
}