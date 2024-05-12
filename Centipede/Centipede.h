#pragma once
#include "GameObject.h"
#include "Segment.h"
#include "Mushroom.h"
#include "Bullet.h"
#include <cmath>
#include<vector>
class lambaKeera :
	public gameObject
{
	//size of lamba keera
	int size;
	//direction, left or right(0,1)
	int direction;
	//bool to determine what to do when in jackson's area
	bool fightmode;
	//array of segments of max size 10 for 
	segment tail[10];
	//bool variables for magic behaviour
	static bool magic;
	static bool drawhead;
public:
	lambaKeera();
	lambaKeera(double x, double y, int s, int d = 1, char t = 'l');
	virtual void collision(gameObject *other, std::vector<gameObject*> &maingame);
	virtual void draw();
	virtual void move();
	
	//timers for magic behaviour
	static void magicOnTimer(int b)
	{
		magic = true;
		glutTimerFunc(15000.0, magicOffTimer, 0);
	}
	static void magicOffTimer(int b)
	{
		magic = false;
		glutTimerFunc(5000.0, magicOnTimer, 0);
	}
	static void DrawOnTimer(int b)
	{
		drawhead = true;
		glutTimerFunc(500.0, DrawOffTimer, 0);
	}
	static void DrawOffTimer(int b)
	{
		drawhead = false;
		glutTimerFunc(500.0, DrawOnTimer, 0);
	}

	~lambaKeera();
};

