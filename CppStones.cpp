#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

struct player
{
	string name;
	int numWins;
};

//function prototypes
string FindPlayerName(player[], bool playerTurn);
int askMove(bool player1Turn, int chipsInPile, player[]);
void getUserNames(player []);
void addWin(player[], bool);

// constants
const int MAX_CHIPS = 100;
const float MAX_TURN = 0.5;

int main(int argc, char** argv)
{
	bool player1Turn = true;
	
	bool gameOver = false;
	int moveCounter = 0;
	int chipsInPile = 0;
	int chipsTaken = 0;
	
	player Players[2];
	char userChoice;
	
	//Output file variabes
	ofstream outFile;
	outFile.open("Winners.txt", ios::app); //append the file rather than overwrite
	
	//seed random number generator
	srand(time(0));
	
	// Ask players for their names
	getUserNames(Players);

	do
	{
		chipsInPile = (rand() % MAX_CHIPS) + 1; //generate random amount of chips
	
		cout << "This round will start with " << chipsInPile << " chips in the pile\n";
		gameOver = false;
	
	while (gameOver == false) //while game is not over
		{
			chipsTaken = askMove(player1Turn, chipsInPile, Players);
			chipsInPile = chipsInPile - chipsTaken;
			cout << "There are " << chipsInPile << " left in the pile\n";
			player1Turn = !player1Turn;
			moveCounter++;
			if (chipsInPile == 0) // if pile is empty
			{
				gameOver = true;
				cout << FindPlayerName(Players , player1Turn) << ", congratulations you won\n";
				outFile << FindPlayerName(Players , player1Turn) << " won in " << moveCounter << " moves\n";
				addWin(Players, player1Turn);
			}
		}
		cout << "Do you want to play again? (Y?N)\n";
		cin >> userChoice;
		userChoice = toupper(userChoice); //incase of user inputting lowercase

	}while (userChoice == 'Y');
	cout << Players[0].name << " had " << Players[0].numWins << " total wins this round" << endl;
	cout << Players[1].name << " had " << Players[1].numWins << " total wins this round" << endl;
	outFile.close();
	return 0;
}

void getUserNames (player Players[])
{
	cout << "Player 1, please enter name: ";
	cin >> Players[0].name;
	cout << "Player 2, please enter name: \n (If you wish to play against the computer, enter 'AI')\n";
	cin >> Players[1].name;
	Players[0].numWins = 0;
	Players[1].numWins = 0;
}

string FindPlayerName(player Players[], bool playerTurn)
{
	if (playerTurn == true)
		return Players[0].name;
	else
		return Players[1].name;
}

int askMove(bool player1Turn, int chipsInPile, player Players[])
{
	int chipsTaken;
	int maxPerTurn = MAX_TURN * chipsInPile; //calculate max amount of chips that can be taken per turn
	do
		{
			cout << FindPlayerName(Players, player1Turn) << " how many chips would you like?\n";
			
			cout << "You can only take up to ";
			if (maxPerTurn == 0)
			{
				cout << " 1\n"; //allow user to take one chip when their is only one chip
			}
			else
			{
				cout << maxPerTurn << endl;
			}
			if (FindPlayerName(Players, player1Turn) == "AI")
				{
					if (maxPerTurn == 0)
					{
						chipsTaken = 1; //allow AI to take one chip when their is only one chip
					}
				else
				{
					chipsTaken = (rand() % maxPerTurn) + 1;
				}
			}
			else
			{
				cin >> chipsTaken;
			}
		} while ((chipsTaken > maxPerTurn) && (chipsInPile > 1)); //while number of chips taken is more than the maximum allowed and their is atleast one chip in the pile
		return chipsTaken;

}

void addWin(player Players[], bool player1Turn)
{
	if (player1Turn)
	{
		Players[0].numWins++;
	}
	else
	{
		Players[1].numWins++;
	}
}
