#pragma once
#include "GameObject.h"

//basically the bullet class
class watta :
	public gameObject
{
public:
	
	virtual void move();
	virtual void collision(gameObject *other, std::vector<gameObject*> &maingame);
	virtual void draw();
	watta(double x=0, double y=0, char t='w');
	~watta();
};

