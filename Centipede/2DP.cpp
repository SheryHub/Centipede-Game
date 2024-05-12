#include "2DP.h"
//default
Position::Position()//just in case for starter
{
	x = NULL;
	y = NULL;
}
//parameterised
Position::Position(double xtemp, double ytemp)// pointer based coordinates
{
	x=new double;
	*x = xtemp;
	//delete []x;
	y = new double;
	*y = ytemp;
	//delete []y;
}
//destructor
Position::~Position()
{
}
