#pragma once
#include "Board.h"
class Position
{
	
public:
	double *x;
	double *y;
	Position();
	Position(double xtemp, double ytemp);
	~Position();
};

