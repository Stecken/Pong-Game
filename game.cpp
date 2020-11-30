#include "game.h"

Game::Game(Player *player1, Player *player2, SDL_Renderer* renderer) {
	this->player1 = player1;
	this->player2 = player2;
	this->renderer = renderer;
	_stateGame = true;
	Game::_pontuacao = 0;
}

void Game::EventWindow(SDL_Event* event) {
	switch (event->type) {
		case SDL_QUIT:
			finalizaGame();
			break;
		default:
			break;
	}
}

void Game::KeyState(const Uint8* keys, int lim) {
	// w && CIMA
	if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_UP]) {
		if (limCima(lim, player2) == 0) {
			player2->positionY += -PASSO;
		}
		if (limCima(lim, player1) == 0) {
			player1->positionY += -PASSO;
		}
	}
	// s && BAIXO
	if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_DOWN]) {
		if (limBaixo(lim, player2) == 0) {
			player2->positionY += +PASSO;
		}
		if (limBaixo(lim, player1) == 0) {
			player1->positionY += +PASSO;
		}
	}
	
	// w && BAIXO
	if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_DOWN]) {
		if (limCima(lim, player2) == 0) {
			player2->positionY += -PASSO;
		}
		if (limBaixo(lim, player1) == 0) {
			player1->positionY += +PASSO;
		}
	}

	// s && CIMA
	if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_UP]) {
		if (limBaixo(lim, player2) == 0) {
			player2->positionY += +PASSO;
		}
		if (limCima(lim, player1) == 0) {
			player1->positionY += -PASSO;
		}
	}

	if (keys[SDL_SCANCODE_W]) {
		if (limCima(lim, player2) == 0) {
			player2->positionY += -PASSO;
		}
	}
	if (keys[SDL_SCANCODE_S]) {
		if (limBaixo(lim, player2) == 0) {
			player2->positionY += +PASSO;
		}
	}
	if (keys[SDL_SCANCODE_UP]) {
		if (limCima(lim, player1) == 0) {
			player1->positionY += -PASSO;
		}
	}
	if (keys[SDL_SCANCODE_DOWN]) {
		if (limBaixo(lim, player1) == 0) {
			player1->positionY += +PASSO;
		}
	}
}

void Game::EventInputKey(SDL_Event* event, int lim) {
	if (event->type == SDL_KEYDOWN) {
		//inputPlayer1(lim, event);
		//inputPlayer2(lim, event);
		if (event->key.keysym.sym == SDLK_w) {
			if (limCima(lim, player2) == 0) {
				player2->positionY += -PASSO;
			}
		}
		if (event->key.keysym.sym == SDLK_UP) {
			if (limCima(lim, player1) == 0) {
				player1->positionY += -PASSO;
			}
		}
		if (event->key.keysym.sym == SDLK_s) {
			if (limBaixo(lim, player2) == 0) {
				player2->positionY += +PASSO;
			}
		}
		if (event->key.keysym.sym == SDLK_DOWN) {
			if (limBaixo(lim, player1) == 0) {
				player1->positionY += +PASSO;
			}
		}
	}
}

void Game::inputPlayer1(int lim, SDL_Event* event) {
	if (event->key.keysym.sym == SDLK_w) {
		if (limCima(lim, player2) == 0) {
			player2->positionY += -PASSO;
		}
	}
	if (event->key.keysym.sym == SDLK_UP) {
		if (limCima(lim, player1) == 0) {
			player1->positionY += -PASSO;
		}
	}
}

void Game::inputPlayer2(int lim, SDL_Event* event) {
	if (event->key.keysym.sym == SDLK_s) {
		if (limBaixo(lim, player2) == 0) {
			player2->positionY += +PASSO;
		}
	}
	if (event->key.keysym.sym == SDLK_DOWN) {
		if (limBaixo(lim, player1) == 0) {
			player1->positionY += +PASSO;
		}
	}
}

int Game::limCima(int lim, Player* player) {
	int posicao = player->positionY;
	if (posicao >= 10) {
		return 0;
	}
	return 1;
}

int Game::limBaixo(int lim, Player* player) {
	int posicao = player->positionY;
	if (posicao < (lim - 20)) {
		return 0;
	}
	return 1;
}

void Game::desenhaPlayer(Player* player) {
	SDL_Rect rectanglePlayer;
	rectanglePlayer.x = player->positionX;
	rectanglePlayer.y = player->positionY;
	rectanglePlayer.w = player->altura;
	rectanglePlayer.h = player->largura;
	SDL_SetRenderDrawColor(renderer, player->corRGB[0], player->corRGB[1], player->corRGB[2], 255);
	SDL_RenderFillRect(renderer, &rectanglePlayer);
	SDL_RenderPresent(renderer);
}

void Game::movePlayer(Player* player, int x, int y) {
	player->positionX += x;
	player->positionY += y;
	desenhaPlayer(player);
}

void limpaTela(SDL_Renderer* renderer) {
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Game::mostraMovimento(Player* player) {
	SDL_Rect rectanglePlayer;
	rectanglePlayer.x = player->positionX;
	rectanglePlayer.y = player->positionY;
	rectanglePlayer.w = player->altura;
	rectanglePlayer.h = player->largura;
	SDL_SetRenderDrawColor(renderer, player->corRGB[0], player->corRGB[1], player->corRGB[2], 255);
	SDL_RenderFillRect(renderer, &rectanglePlayer);
}

bool Game::estadoGame() {
	return _stateGame;
}

void Game::finalizaGame() {
	_stateGame = FINALIZADO;
}