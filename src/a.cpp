#include "a.h"

IOGame::IOGame(SDL_Event& event, Game *Jogo) {
	this->_event = event;
	this->jogo = Jogo;
}