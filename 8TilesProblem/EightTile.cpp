#include "Includes.h"

using namespace std;

bool EightTile::isManual()
{
	
	return manual;
}

int EightTile::hValue()
{
	int h = 0;
	int t;
	int s;
	for (int i = 0; i <3; i++)
	{
		for(int j=0;j<3;j++)
		{
			t = tiles[i][j];
			s = solution[i][j];
			if (t!=s)
			{
				h++;
			}
		}
	}
	
	return h;
	
}

int EightTile::manhattanDistance()
{
	int m=0;
	
	
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			
			for (int k = 0; k<3; k++)
			{
				for (int l = 0; l<3; l++)
				{
					if (tiles[i][j] == solution[k][l])
					{
						m += abs(i - k) + abs(j - l);
					}
				}
			}
			
		}
	}

	return m;
}
int EightTile::iRand(int max)
{
	
	
	
	
	return (int)(rand()*RAND_MAX)%max;
}
void EightTile::randomMove(int movecount)
{
	/*
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tiles[i][j] == 0)
			{
				x = i;
				y = j;
				break;
			}
		}
	}
	*/
	bool moveOK = false;
	
	while(movecount >0)
	{
		
		movecount--;
		
		int move = iRand(4)+1;
		
		switch (move)
		{
		case RIGHT:
			moveOK = okRight();
			setMove(RIGHT);
			break;
		case LEFT:
			moveOK = okLeft();
			setMove(LEFT);
			break;
		case UP:
			moveOK = okUp();
			setMove(UP);
			break;
		case DOWN:
			moveOK = okDown();
			setMove(DOWN);
			break;
		}
		if (moveOK == true)
		{
			cout << "moveok" << endl;
			swap();
			display();
		}
	}
}

EightTile::EightTile(sf::RenderWindow *windowP)
{
	window = windowP;

	TileTextures[0] = new sf::Texture;
	TileTextures[0]->loadFromFile("0.png");

	TileTextures[1] = new sf::Texture;
	TileTextures[1]->loadFromFile("1.png");

	TileTextures[2] = new sf::Texture;
	TileTextures[2]->loadFromFile("2.png");

	TileTextures[3] = new sf::Texture;
	TileTextures[3]->loadFromFile("3.png");

	TileTextures[4] = new sf::Texture;
	TileTextures[4]->loadFromFile("4.png");

	TileTextures[5] = new sf::Texture;
	TileTextures[5]->loadFromFile("5.png");

	TileTextures[6] = new sf::Texture;
	TileTextures[6]->loadFromFile("6.png");

	TileTextures[7] = new sf::Texture;
	TileTextures[7]->loadFromFile("7.png");

	TileTextures[8] = new sf::Texture;
	TileTextures[8]->loadFromFile("8.png");
	
	//myPuzzle.spriteDisplay();
	for(int i = 0;i<3;i++)
	{
		for (int j = 0; j<3;j++)
		{
			sf::RectangleShape *tile = new sf::RectangleShape(sf::Vector2f(200, 200));
			tile->setFillColor(sf::Color::Red);
			tile->setPosition(i * 210, j * 210);
			spriteGrid[i][j] = tile;
	
		}
	}
	myMove = NONE;  //initialize member attributes
	x = 0;  //initial blank position   - make  sure this agrees with solved puzzle!
	y = 0;
	tiles[0][0] = 0; tiles[1][0] = 1; tiles[2][0] = 2; //set up puzzle tiles
	tiles[0][1] = 3; tiles[1][1] = 4; tiles[2][1] = 5;
	tiles[0][2] = 6; tiles[1][2] = 7; tiles[2][2] = 8;

	start[0][0] = 1; start[1][0] = 4; start[2][0] = 2; //set up puzzle tiles
	start[0][1] = 3; start[1][1] = 7; start[2][1] = 0;
	start[0][2] = 6; start[1][2] = 8; start[2][2] = 5;

	solution[0][0] = 0; solution[1][0] = 1; solution[2][0] = 2; //set up solved puzzle tile positions
	solution[0][1] = 3; solution[1][1] = 4; solution[2][1] = 5;
	solution[0][2] = 6; solution[1][2] = 7; solution[2][2] = 8;
	manual = false;
	display();
}
void EightTile::updateGLTiles() {

	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			spriteGrid[i][j]->setTexture(TileTextures[tiles[i][j]]);

		}
	}
}
void EightTile::display(void)
//draw puzzle as it is now
{
	cout << tiles[0][0] << " " << tiles[1][0] << " " << tiles[2][0] << endl;
	cout << tiles[0][1] << " " << tiles[1][1] << " " << tiles[2][1] << endl;
	cout << tiles[0][2] << " " << tiles[1][2] << " " << tiles[2][2] << endl;
	cout << endl;

	updateGLTiles();
	window->clear();

	spriteDisplay();
	window->display();
	
}
void EightTile::spriteDisplay()
{
	//myPuzzle.spriteDisplay();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			
			window->draw(*spriteGrid[i][j]);
		}
	}
}
void EightTile::displayStart(void)
//draw inital puzzle state
{
	cout << "step: 1" << endl;
	cout << "hValue = " << hValue() << endl;
	cout << start[0][0] << " " << start[1][0] << " " << start[2][0] << endl;
	cout << start[0][1] << " " << start[1][1] << " " << start[2][1] << endl;
	cout << start[0][2] << " " << start[1][2] << " " << start[2][2] << endl;
	cout << endl;
	
}

void EightTile::setMove(enum move m)
//sets which way you want to move
{
	myMove = m;
}
void EightTile::swap(void)
//attempts to move blank in direction set - up, down, left or right by doing a tile/blank swap
//can't move beyond edges of puzzle
{
	int temp;
	if (okLeft() & (myMove == LEFT)) {
		temp = tiles[x - 1][y];
		tiles[x - 1][y] = tiles[x][y];
		tiles[x][y] = temp;
		x = x - 1;

	}
	if (okRight() & (myMove == RIGHT)) {
		temp = tiles[x + 1][y];
		tiles[x + 1][y] = tiles[x][y];
		tiles[x][y] = temp;
		x = x + 1;

	}

	if (okUp() & (myMove == UP)) {
		temp = tiles[x][y - 1];
		tiles[x][y - 1] = tiles[x][y];
		tiles[x][y] = temp;
		y = y - 1;

	}
	if (okDown() & (myMove == DOWN)) {
		temp = tiles[x][y + 1];
		tiles[x][y + 1] = tiles[x][y];
		tiles[x][y] = temp;
		y = y + 1;

	}
}
bool EightTile::okLeft(void)
//can I move left?
{

	if (x > 0)
		return true; else return false;
}
bool EightTile::okRight(void)
//can I move right?
{
	if (x < 2)
		return true; else return false;
}
bool EightTile::okUp(void)
//can I move up?
{
	if (y > 0)
		return true; else return false;
}
bool EightTile::okDown(void)
//can I move down?
{
	if (y < 2)
		return true; else return false;
}
//sets up as direction then moves
void EightTile::swapUp()
{
	setMove(UP);
	swap();
}
//sets down as direction then moves
void EightTile::swapDown()
{
	setMove(DOWN);
	swap();
}
//sets left as direction then moves
void EightTile::swapLeft()
{
	setMove(LEFT);
	swap();
}
void EightTile::swapRight()
{
	//sets right as direction then moves
	setMove(RIGHT);
	swap();
}

bool EightTile::manhattanHillClimb()
{
	//use hill climbing to improve solution 1 tile at a time
	//output the current solution on each step
	//1: calc h value by counting the number of correctly placed tiles
	//in the current state
	//for each valid tile move calc h value (as before)

	//select state with best h value (successor) and use this as our current state
	//display
	//wait 1 second
	
	//UNCOMMENT THIS FOR THE PRESET PUZZLE (ALSO IN THE HILL CLIMB BASIC FUNCTION)
	/*
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tiles[i][j] = start[i][j];
		}
	}
	*/
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tiles[i][j] == 0)
			{
				x = i;
				y = j;
				break;
			}
		}
	}
	
	int maxSteps;
	int steps = 0;
	solved = false;
	
	ofstream outputFile;
	
	// create and open the .csv file
	outputFile.open("manhattan.csv");

	// write the file headers
	outputFile << "Steps" << "," << "Manhattan Distance" << std::endl;
	//setting a limit to the amount of steps (doesnt work)
	cout << "would you like to limit the amount of steps the algorithm takes?" << endl;
	cin >> maxSteps;
	while (!solved||maxSteps==steps)
	{
		stepF = steps;
		steps++;
		
		int mdist = manhattanDistance();
		int testResults[4] = { 0, 0, 0, 0 };
		int testResults2[4] = { 0, 0, 0, 0 };
		//make a move, check h, if its smaller set as best move 
		//then make best move afterchecking all
		//(the next 4 if statements)
		if (okUp())
		{
			swapUp();
			testResults[0] = manhattanDistance() - mdist;
			swapDown();
		}
		if (okDown())
		{
			swapDown();
			testResults[1] = manhattanDistance() - mdist;
			swapUp();
		}
		if (okLeft())
		{
			swapLeft();
			testResults[2] = manhattanDistance() - mdist;
			swapRight();
		}
		if (okRight())
		{
			swapRight();
			testResults[3] = manhattanDistance() - mdist;
			swapLeft();
		}
		
		
		//if the difference between the hvalues is 1 or 2 swapup
		//(bitwise or 2 added so the algorithm can traverse corners)
		if (testResults[0] ==-2|| testResults[0] == -1)
		{
			swapUp();
		}
		//if the difference between the hvalues is 1 or 2 swapdown
		//(bitwise or 2 added so the algorithm can traverse corners)
		else if (testResults[1] ==-2|| testResults[1] == -1)
		{
			swapDown();
		}
		//if the difference between the hvalues is 1 or 2 swapleft
		//(bitwise or 2 added so the algorithm can traverse corners)
		else if (testResults[2] ==-2|| testResults[2] == -1)
		{
			swapLeft();
		}
		//if the difference between the hvalues is 1 or 2 swapright
		//(bitwise or 2 added so the algorithm can traverse corners)
		else if (testResults[3]==-2|| testResults[3] ==-1 )
		{
			swapRight();
		}
		else
		{
			randomMove(5);
		}
		//if the puzzle is solved(m=0) finish
		if (manhattanDistance() == 0)
		{
			solved = true;

		}
		cout << "step: " << steps + 1 << endl;
		cout << "manhattan distance = " << manhattanDistance() << endl;
		display();
		// write the data to the output file
		outputFile << steps << "," << manhattanDistance() << endl;


		//timer for moves, may cause the algorithm to take a very long time so its set to very low
		Sleep(100);
	

	}



	cout << "solved in " << steps + 1 << " steps!" << endl;
	// close the output file
	outputFile.close();
	return true;
}

bool EightTile::hillClimbBasic()
{
	//use hill climbing to improve solution 1 tile at a time
	//output the current solution on each step
	//1: calc h value by counting the number of correctly placed tiles
	//in the current state
	//for each valid tile move calc h value (as before)

	//select state with best h value (successor) and use this as our current state
	//display
	//wait 1 second
	
	//UNCOMMENT THIS FOR THE PRESET PUZZLE (ALSO IN manhattanHillClimb THE MANHATTAN HILL CLIMB)
	/*
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tiles[i][j] = start[i][j];
		}
	}
	*/
	 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tiles[i][j] == 0)
			{
				x = i;
				y = j;
				break;
			}
		}
	}
	//seaerch node
	//reference to parent
	//
	ofstream outputFile;

	// create and open the .csv file
	outputFile.open("hillClimbing.csv");

	// write the file headers
	outputFile << "Steps" << "," << "hValue" << std::endl;
	int maxSteps;
	//setting a limit to the amount of steps (doesnt work)
	cout << "would you like to limit the amount of steps the algorithm takes?" << endl;
	cin >> maxSteps;
	int steps = 0;
	solved = false;
	
	while(!solved||maxSteps == steps)
	{
		steps++;
		
		int hval = hValue();
		int testResults[4] = { 1, 1, 1, 1 };
		//make a move, check h, if its smaller set as best move 
		//then make best move afterchecking all
		//(the next 4 if statements)
		if (okUp()) 
		{ 
			swapUp(); 
			testResults[0] = hValue() - hval; 
			swapDown();
		}
		if (okDown())
		{ 
			swapDown(); 
			testResults[1] = hValue() - hval; 
			swapUp();
		}
		if (okLeft())
		{
			swapLeft();
			testResults[2] = hValue() - hval;
			swapRight();
		}
		if (okRight())
		{
			swapRight();
			testResults[3] = hValue() - hval;
			swapLeft();
		}

		//if the difference between the hvalues is 1 or 2 swapup
		//(bitwise or 2 added so the algorithm can traverse corners)
		if (testResults[0] == -1 || testResults[0] == -2)
		{
			swapUp();
		}
		//if the difference between the hvalues is 1 or 2 swapdown
		//(bitwise or 2 added so the algorithm can traverse corners)
		else if(testResults[1] == -1|| testResults[1] == -2)
		{
			swapDown();
		}
		//if the difference between the hvalues is 1 or 2 swapleft
		//(bitwise or 2 added so the algorithm can traverse corners)
		else if (testResults[2] == -1 || testResults[2] == -2)
		{
			swapLeft();
		}
		//if the difference between the hvalues is 1 or 2 swapright
		//(bitwise or 2 added so the algorithm can traverse corners)
		else if (testResults[3] == -1 || testResults[3] == -2)
		{
			swapRight();
		}
		else
		{
			randomMove(5);
		}
		//if the puzzle is solved(h=0) finish
		if (hValue() == 0)
		{
			solved = true;
		}
		cout << "step: " << steps +1 << endl;
		cout << "hValue = " << hValue() << endl;
		display();
		// write the data to the output file
		outputFile << steps << "," << hValue() << endl;

		
		//timer for moves, may cause the algorithm to take a very long time so its set to very low
		Sleep(100);
		
	}
	
	
	outputFile.close();
	cout << "solved in " << steps + 1 << " steps!" << endl;
	return true;
}
