#include "Mushroom.h"
void mushroom::draw()
{
	//draw if active, color depends on lives
	if (active)
	{
		if (lives >= 2)
			DrawSquare(*pos.x, *pos.y, 7, colors[WHITE]);
		else
			DrawSquare(*pos.x, *pos.y, 7, colors[ORANGE_RED]);
	}

}

void mushroom::collision(gameObject *other, std::vector<gameObject*> &maingame)
{
	//code handles collision with wattay or bullets
	if (*pos.x == other->getX() && *pos.y == other->getY())
	{
		if (other->gettype() == 'w')
		{
			if (other->getactive())
			{
				lives--;
				if (lives == 0)
				{
					active = false;
					other->score+=5;

				}
			}
			if(active)
			other->setactive(false);
		}
	}
}

mushroom::mushroom(double x , double y, char t )
{
	*pos.x = x;
	*pos.y = y;
	type = t;	
	lives = 2;
}


mushroom::~mushroom()
{
}
