#include "Segment.h"
segment::segment()
{
}


void segment::draw()
{
	DrawRoundRect(*pos.x, *pos.y, 10, 5, colors[PURPLE], 0.5);
}

void segment::collision(gameObject *other, std::vector<gameObject*> &maingame)
{
}

segment::segment(double segx, double segy):gameObject(segx,segy)// this is??
{
	type = 's';
	
}

segment::~segment()
{
}
