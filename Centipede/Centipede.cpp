#include "Centipede.h"

bool lambaKeera::magic = false;
bool lambaKeera::drawhead = true;

lambaKeera::lambaKeera()
{
	size = 1;
	direction = 1;
	type = 'l';
}


lambaKeera::lambaKeera(double x, double y,  int s, int d, char t ) :gameObject(x, y, t)
{
	if (s > 0)
	{
		direction = d;
		size = s;
		//setup timers
		glutTimerFunc(1.0, magicOffTimer, 0);
		glutTimerFunc(1.0, magicOnTimer, 0);
		glutTimerFunc(1.0, DrawOnTimer, 0);
		glutTimerFunc(1.0, DrawOffTimer, 0);
	}
}
// some code is redundant due to late edits
void lambaKeera::collision(gameObject *other, std::vector<gameObject*> &maingame)
{
	
	if (*pos.x == other->getX() && *pos.y == other->getY())
	{
		//if is mushroom
		if (other->gettype() == 'm')
		{
			if (other->getactive())
			{
				//specialized behaviour depending on fightmode bool
				if (!fightmode)
					*pos.y -= 10;
				else if (fightmode && *pos.y > 60)
				{
					*pos.y = 60;
					fightmode = false;
				}
				else
					*pos.y += 10;
				if (direction == 1)
					direction = 0;
				else if (direction == 0)
					direction = 1;
			}
		}
	}
	for (int i = 1; i < size; i++)
	{
		if (tail[i].getX() == other->getX() && tail[i].getY() == other->getY())
		{
			//this code checks for bullet 
			if (other->gettype() == 'w')
			{ 
				if (other->getactive())
				{
					if (i < size - 1)
					{
						maingame.push_back(new lambaKeera(*pos.x + pow(-1,direction)*20, *pos.y, size - i - 1, !direction));
						num++;

					}
					size = i;
					cout << "tail " << i << "\n";
					score += 10;
					other->setactive(false);
				}
			}
			else if (other->gettype() == 'j')
			{
				if (other->getactive())
				{
					other->setlives(other->getlives() - 1);
					other->setactive(false);
				}
			}
		}
	}
	if (*pos.x == other->getX() && *pos.y == other->getY())
	{
		//only hit if drawhead is on when magic is on, otherwise dont care
		if (other->gettype() == 'w')
		{
			if (magic)
			{
				if(drawhead)
				if (other->getactive())
				{
					if (size <= 1)
					{
						active = false;
						num--;
					}
					else
					{
						size--;
						*pos.x += pow(-1, direction) * 10;
					}
					score += 100;
					other->setactive(false);
				}
			}
			else
				if(other->getactive())
				{
					if (size <= 1)
					{
						active = false;
   						num--;
					}
					else
					{
						size--;
						*pos.x += pow(-1, direction) * 10;
					}					score += 100;
					other->setactive(false);
				}

		}
	}
}

void lambaKeera::draw()
{
	//almost same logic as bfore for drawing
	if (active)
	{
		//cout << "drawing:" << *pos.y << "\n";
		if (magic)
		{
			if (drawhead)
				DrawRoundRect(*pos.x, *pos.y, 10, 5, colors[BLUE], 5);
		}
		else
			DrawRoundRect(*pos.x, *pos.y, 10, 5, colors[BLUE], 5);
		//draw tail
		for (int i = 1; i < size; i++)
			tail[i].draw();
	}
}

void lambaKeera::move()
{
	if (direction == 1)
		*pos.x += 10;
	else if (direction == 0)
		*pos.x -= 10;
	
	//Tail follow code...copied from last semester pf project
	double prevX = tail[0].getX();
	double prevY = tail[0].getY();
	double prev2X, prev2Y;
	tail[0].setX(*pos.x);
	tail[0].setY(*pos.y);
	for (int i = 1; i < size; i++)
	{
		prev2X = tail[i].getX();
		prev2Y = tail[i].getY();
		tail[i].setX(prevX);
		tail[i].setY(prevY);
		prevX = prev2X;
		prevY = prev2Y;
	}

	//almost same logic as before for move
	if (*pos.x >350 || *pos.x<30)
	{
		
		if (!fightmode)
			*pos.y -= 10;
		else if (fightmode && *pos.y > 60)
		{
			*pos.y = 60;
			fightmode = false;
		}
		else if(fightmode)
			*pos.y += 10;

		if (direction == 1)
			direction = 0;
		else if (direction == 0)
			direction = 1;
	}
	if (*pos.y == 0)
	{
		fightmode = true;
	}
}


lambaKeera::~lambaKeera()
{
}
