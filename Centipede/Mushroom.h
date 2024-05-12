#pragma once
#include "GameObject.h"
class mushroom :
	public gameObject
{
public:
	virtual void draw();
	virtual void collision(gameObject *other, std::vector<gameObject*> &maingame);
	mushroom(double x = 0, double y = 0, char t='m');
	//doesnt move so this ftn is left blank
	virtual void move() {};

	~mushroom();
};

