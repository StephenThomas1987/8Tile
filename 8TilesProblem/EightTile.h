#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/GLU.h>
enum move { NONE, UP, DOWN, LEFT, RIGHT };
class EightTile
{
public:
	EightTile(sf::RenderWindow *windowp);  //constructor
	void updateGLTiles();
	void setMove(enum move);  //select direction
	void display(void);	//draw puzzle
	void spriteDisplay();
	void displayStart(void);
	void swap(void); //swap blank with selected tile
	int iRand(int max);
	void randomMove(int);
	bool okLeft(void); //can I move left
	bool okRight(void);//can I move right
	bool okUp(void);//can I move up
	bool okDown(void);//can I move down
	bool hillClimbBasic();//uses local search hill climbing
	bool manhattanHillClimb();
	bool isManual();
	int hValue();
	int manhattanDistance();
	void swapUp();
	void swapDown();
	void swapLeft();
	void swapRight();
	void outputToCSV();
	int stepF;
	//int mdistF;
	bool getSolved()
	{
		return solved;
	}
private:
	sf::RenderWindow *window;
	sf::Texture *TileTextures[9];
	enum move myMove;
	int start[3][3];
	int tiles[3][3];  //puzzle now
	int solution[3][3];//puzzle at start (solved).
	sf::RectangleShape *spriteGrid[3][3];
	int x;  //blank x position
	int y;  //blank y position
	bool manual; // solve manually interacting with console else autosolve
	bool solved = false;
};