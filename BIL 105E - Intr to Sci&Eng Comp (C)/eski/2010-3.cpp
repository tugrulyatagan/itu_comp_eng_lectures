#include <iostream>

using namespace std;

void print_list(int *list, int j)
{
	cout << "Sorted list:  [";
	
	for (int i = 0; i < j; i++)
	{
			cout << list[i] << " ";
	}
	cout << "]" << endl;
}

void sort_list(int *list, int i )
{
	for (int k = 1; k < i + 1; k++)
	{
		for (int l = 0; l < i; l++)
		{
			if(list[l] > list[l + 1])
			{
				int swap = list [l + 1];
				list[l + 1] = list[l];
				list[l] = swap;
			}
		}
	}
}


int main()
{
	int number, *list;
	
	cout << "How many numbers sorted:" << endl;
	cin >> number;
	
	list = new int[number];
	
	for (int i = 0; i < number; i++)
	{
		cout << "Enter number " << "(" << i+1 << ") :";
		cin >> list[i];
		
		sort_list(list,i);
		print_list(list,i+1);
	}

	return 0;
}
