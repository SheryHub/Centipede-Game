#pragma once
#include "GameObject.h"
class segment :
	public gameObject
{
public:
	segment();
	virtual void draw();
	virtual void move() // Not required though
	{};
	virtual void collision(gameObject *other, std::vector<gameObject*> &maingame);
	segment(double segx, double segy);
	~segment();
};

