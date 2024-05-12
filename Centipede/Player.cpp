#include "Player.h"


//this code controls the movement of jackson in accordance with the bool arrays used in game.cpp and declared in gameObject

void jackson::move()
{
	
	//Player left movement
	if (buffer[GLUT_KEY_LEFT] || Pbuffer['a'] ||Pbuffer['A'] /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		*pos.x -= 10;
	}

	//Player right movement
	 if (buffer[GLUT_KEY_RIGHT]||Pbuffer['d'] || Pbuffer['D']/*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		*pos.x += 10;

	}
	
	//Player up movement
	 if (buffer[GLUT_KEY_UP] || Pbuffer['w'] || Pbuffer['W']/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		*pos.y += 10;

	}

	//Player down movement
	if (buffer[GLUT_KEY_DOWN] || Pbuffer['s'] || Pbuffer['S']/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		*pos.y -= 10;

	}


	//Area Bounded for Player
	if (*pos.y > 60)
	{
		*pos.y=60;
	}
	if (*pos.x > 350)
	{
		*pos.x = 350;
	}
	if (*pos.y < 0)
	{
		*pos.y = 0;
	}
	if (*pos.x < 30)
	{
		*pos.x = 30;
	}

}

void jackson::draw()
{
	//draw the player only if it is active
	if (!active)
	{
		srand(time(0));
		int blink = rand() % 2;
		if(blink)
		DrawSquare(*pos.x, *pos.y, 10, colors[GREEN]);
		else
		DrawSquare(*pos.x, *pos.y, 10, colors[ORANGE]);

	}
	else
	DrawSquare(*pos.x, *pos.y, 10, colors[GREEN]);
}

void jackson::collision(gameObject *other, std::vector<gameObject*> &maingame)
{
	//if there is collision with anything other than himself, a bullet or a mushroom, jackson loses a life
	if (*pos.x == other->getX() && *pos.y == other->getY())
	{
		if (other->gettype() != 'j' && other->gettype() != 'm' && other->gettype() != 'w')
		{
			if (active)
			{
				lives--;
				active = false;
			}
		}
	}
}

jackson::~jackson()
{
	delete pos.x;
	delete pos.y;
}
