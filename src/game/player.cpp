#include "player.h"

Player::Player(int positionX, int positionY, int altura, int largura, int corRGB[3]) {
	this->positionX = positionX;
	this->positionY = positionY;
	this->altura = altura;
	this->largura = largura;
	for (int i = 0; i < 3; i++) {
		this->corRGB[i] = corRGB[i];
	}
}