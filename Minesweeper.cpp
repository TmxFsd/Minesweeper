#include <iostream>
#include <iomanip>
#include <vector>
#include<Windows.h>
using namespace std;

class cell
{
private:
	bool state;//0-closed 1-opened
	bool flag;//0-no flag 1-flag placed
	int number;//0-8 number of  mines 9-mine
public:
	cell() :state(0), number(0), flag(0) {}
	//Set
	void SetState(bool state)
	{
		this->state = state;
	}
	void SetFlag(bool flag)
	{
		this->flag = flag;
	}
	void SetNumber(int number)
	{
		this->number = number;
	}
	//Get
	bool GetState() { return state; }
	bool GetFlag()  { return flag; }
	int GetNumber() { return number; }
	//NumUp
	void NumUp()
	{
		number+=1;
	}
	//Show
	void ShowNumber()
	{
		cout << " "<< number;
	}
	void ShowState()
	{
		cout <<" " << state;
	}
};

//Main functions
void DrawField(vector<vector<cell>> obj, int const size, HANDLE cons)
{
	int bgColor = 128;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (obj[i][j].GetState() == 0)
			{
				SetConsoleTextAttribute(cons, bgColor +7);
				cout << " |";
			}
			else
			{
				if (obj[i][j].GetNumber() == 1)
				{
					SetConsoleTextAttribute(cons, bgColor + 1);
					cout << " 1";
				}
				else if (obj[i][j].GetNumber() == 2)
				{
					SetConsoleTextAttribute(cons, bgColor + 2);
					cout << " 2";
				}
				else if (obj[i][j].GetNumber() == 3)
				{
					SetConsoleTextAttribute(cons, bgColor + 4);
					cout << " 3";
				}
				else if (obj[i][j].GetNumber() == 4)
				{
					SetConsoleTextAttribute(cons, bgColor + 9);
					cout << " 4";
				}
				else if (obj[i][j].GetNumber() == 5)
				{
					SetConsoleTextAttribute(cons, bgColor + 12);
					cout << " 3";
				}
				else if (obj[i][j].GetNumber() == 6)
				{
					SetConsoleTextAttribute(cons, bgColor + 11);
					cout << " 6";
				}
				else if (obj[i][j].GetNumber() == 7)
				{
					SetConsoleTextAttribute(cons, bgColor + 5);
					cout << " 7";
				}
				else if (obj[i][j].GetNumber() == 8)
				{
					SetConsoleTextAttribute(cons, bgColor +8);
					cout << " 8";
				}
				//FOR DEBUGGING PURPUSE
				else if (obj[i][j].GetNumber() == 9)
				{
					SetConsoleTextAttribute(cons, bgColor + 0);
					cout << " *";
				}
				/////
				else
				{
					cout << "  ";
				}

			}
		}
		cout << "\n";
	}
	SetConsoleTextAttribute(cons, 7);
}
void FillBombs(vector<vector<cell>>& obj, int const size)
{
	int x;
	int y;
	int numBomb;
	bool loop=1;

	if (size == 8) numBomb = 10;
	else if (size == 16) numBomb = 32;
	else numBomb = size;

	for (int i = 0; i < numBomb; i++)
	{
		loop = 1;
		do
		{
			x = rand() % size;
			y = rand() % size;
			if (obj[x][y].GetNumber() == 0)
			{
				obj[x][y].SetNumber(9);
				loop = 0;
			}
		} while (loop);
		
	}
}
void SetNumbers(vector<vector<cell>>& obj, int const size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			//Too much conditions, find beter way
			if (obj[i][j].GetNumber() == 9)
			{
				if (i > 0)
					if (obj[i - 1][j].GetNumber() != 9)
						obj[i - 1][j].NumUp();

				if (j > 0)
					if (obj[i][j - 1].GetNumber() != 9)
						obj[i][j - 1].NumUp();
				
				if (i > 0 and j > 0)
					if (obj[i - 1][j - 1].GetNumber() != 9)
						obj[i - 1][j - 1].NumUp();

				if (i < size-1)
					if (obj[i + 1][j].GetNumber() != 9)
						obj[i + 1][j].NumUp();

				if (j < size-1)
					if (obj[i][j + 1].GetNumber() != 9)
						obj[i][j + 1].NumUp();

				if (i < size-1 and j < size-1)
					if (obj[i + 1][j + 1].GetNumber() != 9)
						obj[i + 1][j + 1].NumUp();

				if (i > 0 and j < size-1)
					if (obj[i - 1][j + 1].GetNumber() != 9)
						obj[i - 1][j + 1].NumUp();

				if (i < size-1 and j > 0)
					if (obj[i + 1][j - 1].GetNumber() != 9)
						obj[i + 1][j - 1].NumUp();
			}
		}
	}
}


//Development functions
void ShowStateAll(vector<vector<cell>>& obj, int const size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			obj[i][j].ShowState();
		}
		cout << "\n";
	}
	cout << "\n";
}
void ShowNumberAll(vector<vector<cell>>& obj, int const size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			obj[i][j].ShowNumber();
		}
		cout << "\n";
	}
	cout << "\n";
}
void fillField(vector<vector<cell>>& obj, int const size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			obj[i][j].SetState(1);
			//obj[i][j].SetFlag(0);
			//obj[i][j].SetNumber(rand() % 8);
		}
}


int main()
{
	int const size_easy = 8;
	cell Cell;
	vector<vector<cell>>Field;

	HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));

	SetConsoleTextAttribute(cons, 135);


	for (int i = 0; i < size_easy; i++)
	{
		vector<cell>column;
		for (int j = 0; j < size_easy; j++)
			column.push_back(Cell);
		Field.push_back(column);
	}
	ShowNumberAll(Field, size_easy);

	//fillField(Field, size_easy);
	//ShowStateAll(Field, size_easy);
	//DrawField(Field, size_easy, cons);
	//ShowNumberAll(Field, size_easy);

	FillBombs(Field, size_easy);
	ShowNumberAll(Field, size_easy);
	SetNumbers(Field, size_easy);
	ShowNumberAll(Field, size_easy);
	fillField(Field, size_easy);
	DrawField(Field, size_easy,cons);


}

//Test for git

//second test for git
