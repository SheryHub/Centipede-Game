#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_

#include "util.h"
#include "Board.h"
#include "2DP.h"
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Mushroom.h"
#include "Centipede.h"
#include "Flea.h"
#include "Spider.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath> 
#include "game.h"

using namespace std;

//game state enum
enum gameState { win, lose, paused, start, play };


int state = start;// Defining state to be 3


//level controllers
int level = 1;
int current_level = 1;


//global bool variables for different mechanics
bool shoot = true, makeflea = true, makemushroom = true, makeheads = false, reset = false, makri_present=false;


//numofshrooms to tell how many mushrooms in game
int numofshrooms = rand() % 11 + 20;


//counts mushrooms in player area to make flea
int fleacount = 0;
Board *b;


//game vector that has all objects and controls the whole game
vector<gameObject*> m;
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


void positionfactory(int &randx, int &randy, int i, std::vector<gameObject*> &randset)
{
	//position factory generates positions that are multiples of 10 and 20..this helps the collision mechanism
	while (randx % 10 != 0 || randy % 20 != 0)
	{
		randx = rand() % 321+30;
		randy = rand() % 331+20;
		for (int j = 0; j < i; j++)
		{
			if (randx == randset[j]->getX() && randy == randset[j]->getY())
			{
				positionfactory(randx, randy, i, randset);
			}
		}
	}

}


//feeds the coordinates generated in position factory to make new mushrooms
void mushroomFactory(std::vector<gameObject*> &randset)
{
	srand(time(0));
	int randx = -3, randy = -3;
	for (int i = 0; i < numofshrooms; i++)
	{
		positionfactory(randx, randy, i, randset);
		randset.push_back(new mushroom(randx, randy));
		randx = -3, randy = -3;

	}
}


void GameDisplay(){


	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	


//       GAME START

	if (state == play)
	{
		//random variables to use later with position factory 
		int rx = -3, ry = -3;

		//checks if space is pressed and shoot is true
		if ((*m.begin())->Pbuffer[32] && shoot)
		{
			m.push_back(new watta((*m.begin())->getX(), (*m.begin())->getY(), 'w'));
			shoot = false;
		}

		DrawString(40, 380, "Score: " + to_string((*m.begin())->score), colors[WHITE]);
		DrawString(320, 380, "Lives: " + to_string((*m.begin())->getlives()), colors[WHITE]);
		DrawString(150, 380, "\"U\" to PAUSE", colors[BLUE]);
		DrawRectangle(0, 0, 20, 340, colors[PURPLE]);
		DrawRectangle(370, 0, 50, 340, colors[PURPLE]);


		auto i = m.begin();
		//variable used to make heads while lamba keera is in player area, controls making heads on left or right side
		int k;
		makri_present = false;
		//this is the loop that makes the majority of the game work
		for (i = m.begin(); i != m.end(); k++,i++)
		{
			k = 0;
			
			//call draw and move for all objects
			(*i)->draw();
			(*i)->move();
			
			//used for making flea, checks mushrooms in player area
			if ((*i)->gettype() == 'm')
			{
				if ((*i)->getY() <= 60)
					if((*i)->getactive())
						fleacount++;
			}
			//used to make mushrooms when flea is made, depends on a few variables that work with random numbers and timers
			if ((*i)->gettype() == 'f')
			{
				if((*i)->getactive())
				if ((*i)->getlives() == 1 && makemushroom)
				{
					m.push_back(new mushroom((*i)->getX(), (*i)->getY()));
					makemushroom = false;
				}
			}
			//makes heads if lamba keera is in player area, rate increases as more are made
			if ((*i)->gettype() == 'l')
			{
				if ((*i)->getY() <= 60)
				{
					if (makeheads)
					{
						while(ry%10!=0)
							ry = rand() % 60;

						if (k % 2)
							m.push_back(new lambaKeera(40, ry, 1));
						else
							m.push_back(new lambaKeera(340, ry, 0));
						(*i)->num++;
						makeheads = false;
					}
				}
			}
			//deletes objects from vector if they are not active
			if ((*i)->gettype() != 'j')
			{
				if ((*i)->getactive() == false)
				{
  					i=m.erase(i)-1;
				}
			}
			//if player dies, makes lambakeera at top again, destroys all others
			if ((*i)->gettype() == 'j')
			{
				if ((*i)->getactive() == false)
				{
					for (auto j = m.begin(); j != m.end(); j++)
					{
						if ((*j)->gettype() == 'l' || (*j)->gettype() == 'm' || (*j)->gettype()=='s')
							(*j)->setactive(false);
					}
					reset = true;
					if (reset)
					{
						m.erase(m.begin() + 1, m.end());
						m.push_back(new lambaKeera(170, 340, 10));
						mushroomFactory(m);
						reset = false;
						(*i)->setactive(true);
						(*i)->num = 1;
					}
				}
			}
			if ((*i)->gettype() == 's')
			{
				makri_present = true;
			}
			//this nested loop checks for collision with all other objects by calling the collision function
			for (auto j = m.begin(); j != m.end(); j++)
			{
				if (j != i)
					(*i)->collision(*j, m);
			}
		}
		if (!makri_present && !makeflea)
		{
			m.push_back(new MakriMan((rand() % 31 + 5) * 10, 90));
			makri_present = true;
		}
		//make a position for flea
		positionfactory(rx, ry, 1, m);
		//make flea depending on timer and random variables
		if (fleacount <= 3 && makeflea)
		{
			m.push_back(new Flea(rx, 200));
			makeflea = false;
		}
		//set flea count to zero each frame after checks are made along with fleas
		fleacount = 0;
		//change states
		if ((*m.begin())->getlives() <= 0)
			state = lose;
		//next level if num of lambay keeray is <=0
		else if ((*m.begin())->num <= 0)
		{
			level++;
			m.erase(m.begin()+1, m.end());
			numofshrooms += (0.20)*numofshrooms;
			mushroomFactory(m);
			if (level != 11)
				m.push_back(new lambaKeera(170, 340, 11 - level));
			else
				state = win;
			int xpos, i; 
			for (i = 0; i < level - 1; i++)
			{
				xpos = (rand() % 31 + 3) * 10;
				m.push_back(new lambaKeera(xpos, 340, 1));
			}
			(*m.begin())->num = i + 1;

		}
		else if ((*m.begin())->Pbuffer['U'] || (*m.begin())->Pbuffer['u'])
		{
			state = paused;
		}
	}
	//menus and screens
	else if (state == start || state==lose || state==win)
	{
		int color = rand() % 70;
		DrawString(25, 350, "WELCOME TO WATTAY MAAR",colors[color]);
		DrawString(70, 330, "KEERAY MAAR", colors[color]);
		DrawString(50, 250, "Press enter to play", colors[WHITE]);
		DrawString(60, 200, "Esc to close", colors[WHITE]);
		if (state == lose)
		{
			DrawString(70, 10, "Score: " + to_string((*m.begin())->score), colors[color]);
			DrawString(60, 50, "Shery Died :/", colors[color]);
		}
		else if (state == win)
		{
			DrawString(70, 10, "Score: " + to_string((*m.begin())->score), colors[color]);

			DrawString(60, 50, "Shery Didn't Die :/", colors[color]);
		}
		if ((*m.begin())->Pbuffer[13])
		{
			(*m.begin())->setlives(3);
			m.erase(m.begin(),m.end()); 
			m.push_back(new jackson(200, 0));
			mushroomFactory(m);
			m.push_back(new lambaKeera(170, 340, 10));
			state = play;
		}
		else if((*m.begin())->Pbuffer[27])
			exit(0);
	}
	else if (state == paused)//remember the change here as well pause->paused
	{
		DrawString(70, 10, "Score: " + to_string((*m.begin())->score), colors[WHITE]);
		DrawString(60, 50, "PAUSED \"M\" to Play", colors[BLUE]);
		DrawString(60, 80, "Level "+to_string(level), colors[BLUE]);

		if ((*m.begin())->Pbuffer['m'] || (*m.begin())->Pbuffer['M'])
			state = play;
	}
	glutSwapBuffers(); // do not modify this line..

}


//these functions set values in the buffer and Pbuffer arays to true if the keys are pressed, and to false if they are released


//leading to smooth movement in the game, to understand
void NonPrintableKeys(int key, int x, int y) 
{
	(*m.begin())->buffer[key] =true;
}
void NonPrintableUp(int key, int x, int y) 
{
	(*m.begin())->buffer[key] = false;
}
void PrintableKeys(unsigned char key, int x, int y) {
	(*m.begin())->Pbuffer[key] = true;
}
void PrintableKeysUp(unsigned char key, int x, int y) 
{
	(*m.begin())->Pbuffer[key] = false;
}


//timer to control game speed
void Timer(int m) {
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}


//timer to control blinking in Shery when he dies
void SheryBlinkTimer(int b) 
{
	(*m.begin())->setactive(true);
	glutTimerFunc(5000.0, SheryBlinkTimer, 0);
}


//timer to control amount of bullets
void bulletTimer(int b)
{
	shoot = true;
	glutTimerFunc(250.0, bulletTimer, 0);
}


//timer to control making of fleas
void fleaTimer(int b)
{
	makeflea = true;
	glutTimerFunc(10000.0, fleaTimer, 0);
}


//timer to control making of mushrooms by fleas
void mushroomTimer(int b)
{
	makemushroom = true;
	glutTimerFunc(500.0, mushroomTimer, 0);
}


//timer to control making of lamba keera heads in player area
void headTimer(int b)
{
	makeheads = true;

	glutTimerFunc(10000.0, headTimer, 0);

}




int main(int argc, char*argv[]) {

	b = new Board(10, 10); // create a new board object to use in the Display Function ...
	int width = 400, height = 400; // i have set my window size to be 800 x 600
	b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("  THE CENITPEDE GAME BY SHAHERYAR"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	glutDisplayFunc(GameDisplay); 
	glutSpecialFunc(NonPrintableKeys); 
	glutSpecialUpFunc(NonPrintableUp); 

	glutKeyboardFunc(PrintableKeys); 
	glutKeyboardUpFunc(PrintableKeysUp);
	
	glutTimerFunc(1.0, Timer, 0);
	glutTimerFunc(1.0, SheryBlinkTimer, 0);
	glutTimerFunc(1.0, bulletTimer, 0);
	glutTimerFunc(1.0, fleaTimer, 0);
	glutTimerFunc(1.0, mushroomTimer, 0);
	glutTimerFunc(1.0, headTimer, 0);

	
//initial push of objects into the main game vector
	m.push_back(new jackson(200, 0));
	mushroomFactory(m);
	m.push_back(new lambaKeera(170, 330, 10));

	
	glutMainLoop();
	return 1;
}
#endif 
