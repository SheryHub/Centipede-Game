#include "GameObject.h"

//initial value of num of centipedes and score
int gameObject::num = 1;
int gameObject::score = 0;

//setter and getters
int gameObject::getnum() const
{
	return num;
}

void gameObject::setnum(int n)
{
	num = n;
}


bool gameObject::getactive() const
{
	return active;
}

int gameObject::getlives() const
{
	return lives;
}

void gameObject::setlives(int l)
{
	lives = l;
}

void gameObject::setactive(bool a)
{
	active = a;
}

//parameterised constructor
gameObject::gameObject(double x, double y, char t)
{
	pos=Position(x, y);
	type = t;
	active = true;
}

void gameObject::setX(double x)
{
	*pos.x = x;
}

void gameObject::setY(double y)
{
	*pos.y = y;
}

double gameObject::getX() const
{
	return *pos.x;
}

double gameObject::getY() const
{
	return *pos.y;
}

gameObject::~gameObject()
{
}
