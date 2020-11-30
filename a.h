#pragma once
#ifndef A_H_
#include "game.h"


class IOGame {
public:
	Game* jogo;
	SDL_Event _event;
	IOGame(SDL_Event& event, Game* Jogo);
	void EventWindow();
	void EventInputKey();
private:
};

#endif // !IO_H_
