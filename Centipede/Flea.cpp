#include "Flea.h"
void Flea::move()
{
	//lives variable is used to determin the probability of the Flea leaving behind mushrooms, moves straight down
	srand(time(0));
	if (active)
	{
		lives = rand() % 4 + 1;
		*pos.y -= 10;
	}
	if (*pos.y < 0)
		active = false;

}

void Flea::draw()
{
	if(active)
	DrawString(*pos.x+5, *pos.y, "i", colors[YELLOW]);
}

void Flea::collision(gameObject * other, std::vector<gameObject*>& maingame)
{
	//collision with watta sets active to false
	if (*pos.x == other->getX() && *pos.y == other->getY())
	{
		if (other->gettype() == 'w')
		{
			if (other->getactive())
			{
				active = false;
				other->score += 200;
			}
			if (active)
				other->setactive(false);
		}
	}
}

Flea::~Flea()
{
}
