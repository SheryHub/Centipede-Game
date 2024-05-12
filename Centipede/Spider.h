#pragma once
#include "GameObject.h"
class MakriMan :
	public gameObject
{
	bool vertical;
	bool horizontal;
public:
	MakriMan(double x, double y, char t = 's') :gameObject(x, y, t)
	{
		lives = 1;
	}	

	virtual void move();
	virtual void draw();
	virtual void collision(gameObject *other, std::vector<gameObject*> &maingame);
	
	~MakriMan();
};

