#pragma once
#include"2DP.h"
#include "util.h"


// moveable is included


class gameObject
{
protected:
	
	bool active;//decides if the object will be present in the game or not
	Position pos;//gameObject has a position (x & y)
	char type;//determine the type of the object
	int lives;//determine its lives
	
public:
	gameObject(double x = 0, double y = 0, char t = ';');

	//these arrays are used to control the inputs, more explanation in game.cpp
	bool buffer[256];
	bool Pbuffer[256];
	//score and num of centipedes or lambay Keeray in the game
	static int score;
	static int num;
	//getters and setters
	int getnum() const;
	void setnum(int n);
	bool getactive() const;
	int getlives() const;
	void setlives(int l);
	void setactive(bool a);
	void setX(double x);
	void setY(double y);
	double getX() const;
	double getY() const;
	char gettype() const
	{
		return type;
	}
	
	//collision function, takes the object to check collision with and the vector in which the game is working
	virtual void collision(gameObject *other, std::vector<gameObject*> &maingame) = 0;
	//virtual move and draw functions, mushroom does not use the move function
	virtual void draw() = 0;
	virtual void move() = 0;
	
	~gameObject();

	
};

