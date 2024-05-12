
 // THE PLAYER CLASS

#pragma once
#include "GameObject.h"
#include "util.h"
#include <ctime>
#include<cstdlib>

class jackson :
	public gameObject
{
public:	
	
	virtual void move();
	virtual void draw();
	virtual void collision(gameObject *other, std::vector<gameObject*> &maingame);
	
	jackson(double x, double y, char t='j') :gameObject(x, y, t)
	{
		lives = 3;
	}
	
	
	~jackson();
};

