#pragma once
#ifndef GAME_H_
#include "libsgame.h"
#include "player.h"
#define JOGANDO true
#define FINALIZADO false
#define RETURN_ERROR 1
#define ERROR_GAME 0
#define PASSO 10

class Game {
public:
	Game(Player* player1, Player* player2, SDL_Renderer* renderer);
	Player* player1;
	Player* player2;
	SDL_Renderer* renderer;
	void EventWindow(SDL_Event* event);
	void KeyState(const Uint8* keys, int lim);
	void EventInputKey(SDL_Event* event, int lim);
	void inputPlayer1(int lim, SDL_Event* event);
	void inputPlayer2(int lim, SDL_Event* event);
	int limCima(int lim, Player* player);
	int limBaixo(int lim, Player* player);
	void desenhaPlayer(Player* player);
	void movePlayer(Player* player, int x, int y);
	void mostraMovimento(Player* player);
	bool estadoGame();
	void finalizaGame();
private:
	int _pontuacao;
	bool _stateGame;
};

void limpaTela(SDL_Renderer* renderer);



#endif // !PLAYERS_H_
