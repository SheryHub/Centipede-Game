#include "Spider.h"


void MakriMan::move()
{
	if (vertical)
		*pos.y += 10;
	else
		*pos.y -= 10;
	if (horizontal)
		*pos.x += 10;
	else
		*pos.x -= 10;

	if (*pos.x < 30)
		horizontal = true;
	else if (*pos.x > 330)
		horizontal = false;
	if (*pos.y > 100)
		vertical = false;
	else if (*pos.y < 40)
		vertical = true;
}

void MakriMan::draw()
{
	if (active)
	{
		DrawRoundRect(*pos.x+5, *pos.y, 5, 5, colors[TOMATO], 10);
	}
}

void MakriMan::collision(gameObject * other, std::vector<gameObject*>& maingame)
{
	if (*pos.x == other->getX() && *pos.y == other->getY())
	{
		if (other->getactive())
		{
			if (other->gettype() == 'm')
				other->setactive(false);
			else if (other->gettype() == 'w')
			{
				if (*pos.y - other->getY() <= 20)
					score += 900;
				else if (*pos.y - other->getY() > 20 && *pos.y - other->getY() <= 50)
					score += 600;
				else
					score += 300;
					active = false;
			}
		}
	}
}

MakriMan::~MakriMan()
{
}
