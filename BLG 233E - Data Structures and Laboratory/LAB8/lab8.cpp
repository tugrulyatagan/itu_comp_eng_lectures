// ahmet aycan atak

#include <iostream>
using namespace std;

#define MAZESIZE_X 8
#define MAZESIZE_Y 8

enum { LEFT, RIGHT, UP, DOWN };

struct cell
{
	bool left, right, up, down;
	char val;
	bool visited;
};

cell m[MAZESIZE_X][MAZESIZE_Y];
int exit_x;
int exit_y;

void print()
{
	for (int i=0; i< MAZESIZE_Y; i++)
	{
		for (int j=0; j<MAZESIZE_X; j++)
		{
			if (m[i][j].up)
				cout << " -";
			else
				cout << "  ";
		}
		cout << endl;
		cout << "|";
		for (int j=0; j<MAZESIZE_X; j++)
		{
			if (m[i][j].right)
				cout << m[i][j].val << "|";
			else
				cout << m[i][j].val << " ";
		}
		cout << endl;
	}
	for (int i=0; i<MAZESIZE_X; i++)
		if (m[MAZESIZE_Y-1][i].down)
			cout << " -";
	cout << endl;
}

void print_new()
{
	for (int i=0; i< MAZESIZE_Y; i++)
	{
		cout << "X";
		for (int j=0; j<MAZESIZE_X; j++)
		{
			if (m[i][j].up)
				cout << "XX";
			else
				cout << " X";
		}
		cout << endl;
		cout << "X";
		for (int j=0; j<MAZESIZE_X; j++)
		{
			if (m[i][j].right)
				cout << m[i][j].val << "X";
			else
				cout << m[i][j].val << " ";
		}
		cout << endl;
	}
	cout << "X";
	for (int i=0; i<MAZESIZE_X; i++)
		if (m[MAZESIZE_Y-1][i].down)
			cout << "XX";
	cout << endl;
}

void initialize()
{
	for (int i=0; i<MAZESIZE_Y; i++)
	{
		for (int j=0; j<MAZESIZE_X; j++)
		{
			m[i][j].up = true;
			m[i][j].down = true;
			m[i][j].right = true;
			m[i][j].left = true;
			m[i][j].val = ' ';
			m[i][j].visited = false;
		}
	}
}

void recursive_maze_generation(int i, int j)
{
	m[i][j].visited = true;
	while (true)
	{
		// gidilemeyen hücre var mi kontrolu
		int counter = 0;
		if (i-1>=0)
			if (m[i-1][j].visited == false)
				counter++;
		if (i+1<MAZESIZE_Y)
			if (m[i+1][j].visited == false)
				counter++;
		if (j-1>=0)
			if (m[i][j-1].visited == false)
				counter++;
		if (j+1<MAZESIZE_X)
			if (m[i][j+1].visited == false)
				counter++;
		if (counter == 0)
			return;
		int r = rand()%4;
		// r = 0 yukari gitme olsun
		if (r == 0 && i-1>=0)
		{
			if (m[i-1][j].visited==false)
			{
				m[i][j].up = false;
				m[i-1][j].down = false;
				recursive_maze_generation(i-1,j);
			}
		}
		// r = 1 asagi gitme olsun
		if (r == 1 && i+1<MAZESIZE_Y)
		{
			if (m[i+1][j].visited==false)
			{
				m[i][j].down = false;
				m[i+1][j].up = false;
				recursive_maze_generation(i+1,j);
			}
		}
		// r = 2 saga gitme olsun
		if (r == 2 && j+1<MAZESIZE_X)
		{
			if (m[i][j+1].visited==false)
			{
				m[i][j].right = false;
				m[i][j+1].left = false;
				recursive_maze_generation(i,j+1);
			}
		}
		// r = 3 sola gitme olsun
		if (r == 3 && j-1>=0)
		{
			if (m[i][j-1].visited==false)
			{
				m[i][j].left = false;
				m[i][j-1].right = false;
				recursive_maze_generation(i,j-1);
			}
		}
	}
}

bool find_path(int x, int y, int camefrom){
	m[x][y].val = 'o';
	if(x == exit_x && y == exit_y)
		return true;
	print();
	if(y > 0 && !m[x][y-1].right && camefrom != LEFT)
		if(find_path(x,y-1,RIGHT)) //left
			return true;
	if(x < MAZESIZE_X-1 && !m[x+1][y].up && camefrom != DOWN)
		if(find_path(x+1,y,UP)) //down
			return true;
	if(x > 0 && !m[x-1][y].down && camefrom != UP)
		if(find_path(x-1,y,DOWN)) //up
			return true;
	if(y < MAZESIZE_Y-1 && !m[x][y+1].left && camefrom != RIGHT)
		if(find_path(x,y+1,LEFT)) //right
			return true;
	m[x][y].val = ' '; //incorrect paths deleted
	print(); //the return path is also viewed
	return false;
}


int main()
{
	initialize();
	recursive_maze_generation(0,0);
	print();
	cout << "Please enter the exit coordinates: " << endl;
	cout << "x: ";
	cin >> exit_x;
	cout << "y: ";
	cin >> exit_y;
	if(find_path(0,0, LEFT))
		cout << "PATH found" <<endl;
	print();
	system("pause");
	return 0;
}