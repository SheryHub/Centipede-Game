#include "Bullet.h"




void watta::move()
{
	//sets active false if bounds are crossed
	if (*pos.y < 350 && active)
		*pos.y += 10;
	else
	{
		active = false;
	}
}

void watta::collision(gameObject *other, std::vector<gameObject*> &maingame)
{
	//set active false if collides with lamba keera
	if (*pos.x == other->getX() && *pos.y == other->getY())
	{
		if (other->gettype() == 'l')
			active = false;
	}
}

void watta::draw()
{
	if(active)
	DrawRoundRect(*pos.x+3, *pos.y, 3,5, colors[RED],0.1);
}

watta::watta(double x, double y, char t):gameObject(x,y,t)
{
	active = true;
	move();
}



watta::~watta()
{
}
