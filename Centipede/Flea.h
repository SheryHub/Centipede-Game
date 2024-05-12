#pragma once
#include "GameObject.h"
class Flea :
	public gameObject
{

public:
	Flea(double x, double y, char t = 'f') :gameObject(x, y, t)
	{};
	virtual void move();
	virtual void draw();
	virtual void collision(gameObject *other, std::vector<gameObject*> &maingame);
	~Flea();
};

