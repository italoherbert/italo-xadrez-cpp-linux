#include "peca_mov.h"

PecaMov::PecaMov( int x1, int y1, int x2, int y2, bool isComp ) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->deComp = isComp;
}

int PecaMov::getX1() {
	return x1;
}

int PecaMov::getY1() {
	return y1;
}

int PecaMov::getX2() {
	return x2;
}

int PecaMov::getY2() {
	return y2;
}

bool PecaMov::isDeComp() {
	return deComp;
}

