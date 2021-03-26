#pragma once
#ifndef PLAYERS_H_

class Player {
public:
	Player(int positionX, int positionY, int altura, int largura, int corRGB[3]);
	int positionX;
	int positionY;
	int altura;
	int largura; 
	int corRGB[];
private:
};

#endif // !PLAYERS_H_
