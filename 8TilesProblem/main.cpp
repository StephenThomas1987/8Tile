#include "Includes.h"


using namespace std;





int main(void)
{
	srand(static_cast <unsigned> (time(0)));


	//simple program to exercise puzzle by moving blank around
	//and drawing tiles
	char d; //keyboard interface valid values a,s,w,d	
	
	//SFML graphics stuff
	sf::RenderWindow window(sf::VideoMode(900, 900), "8Tile Problem", sf::Style::Default);


	EightTile myPuzzle(&window);//create class and init.

	myPuzzle.randomMove(25);
	int chooseVar = 0;

	cout << "Would you like to 1: manual puzzle 2: Basic hill climb 3: Manhattan distance hill climb" << endl;
	cin >> chooseVar;
	if (myPuzzle.isManual() == true)
	{
		while (!myPuzzle.getSolved()) //go forever
		{	
			sf::Event evnt;
			while (window.pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					evnt.key;
					if (chooseVar==1)
					{
						printf("%c\n", evnt.key.code);
						//cin >> d;
						d = evnt.key.code;
						if (d == sf::Keyboard::A) myPuzzle.setMove(LEFT);
						if (d == sf::Keyboard::D) myPuzzle.setMove(RIGHT);
						if (d == sf::Keyboard::W) myPuzzle.setMove(UP);
						if (d == sf::Keyboard::S) myPuzzle.setMove(DOWN);
						myPuzzle.swap(); //move blank
						myPuzzle.display(); //draw puzzle

					}
					
					
				}
			}
		}
	}
	else if (chooseVar == 2)
	{
		myPuzzle.hillClimbBasic();
	}
	else if (chooseVar == 3)
	{
		myPuzzle.manhattanHillClimb();
	}
	
	
	char response;
	cin >> response;
	return 0;
}//the end